#include "direntry.h"
#include "utils.h"
#include "apidisk.h"
#include "bitmap.h"
#include "superblock.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

DirEntry* gp_currentDirEntry = NULL;

// Serializes the DirEntry to write to disk
// The buffer should have size == 256
void
serialize_DirEntry(DirEntry* s_dirEntry, unsigned char* buffer)
{
	// Temp buffer
	unsigned char* tempBuffer = calloc(SECTOR_SIZE, sizeof(unsigned char));
	// Add name to temp buffer
	memcpy(tempBuffer, s_dirEntry->m_name, sizeof(s_dirEntry->m_name));
	// Add filetype to temp buffer
	// Shifts starting position
	memcpy(tempBuffer + sizeof(s_dirEntry->m_name), &s_dirEntry->m_filetype, sizeof(s_dirEntry->m_filetype));
	// Add size to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype),
		&s_dirEntry->m_size, 
		sizeof(s_dirEntry->m_size));
	// Add iBlockAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size),
		&s_dirEntry->m_iBlockAddress, 
		sizeof(s_dirEntry->m_iBlockAddress));
	// Add parentAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress),
		&s_dirEntry->m_parentAddress, 
		sizeof(s_dirEntry->m_parentAddress));
	// Add ownAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*2,
		&s_dirEntry->m_ownAddress, 
		sizeof(s_dirEntry->m_ownAddress));
	// Add entries to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*3,
		&s_dirEntry->m_entries, 
		sizeof(s_dirEntry->m_entries));
	// Add empty to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*3  + sizeof(s_dirEntry->m_entries),
		&s_dirEntry->m_empty, 
		sizeof(s_dirEntry->m_empty));

	memcpy(buffer, tempBuffer, sizeof(DirEntry));
}

// Deserializes the DirEntry to read from disk
// The buffer should have size == 256
DirEntry* 
deserialize_DirEntry(unsigned char* buffer)
{
	// Returned read dir
	DirEntry* readDir = malloc(sizeof(DirEntry));

	// Add name to new struct
	memcpy(readDir->m_name, buffer, sizeof(readDir->m_name));
	// Add filetype to new struct
	// Shifts starting position
	memcpy(&readDir->m_filetype, buffer + sizeof(readDir->m_name), sizeof(readDir->m_filetype));
	// Add size to new struct
	memcpy(
		&readDir->m_size,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype),
		sizeof(readDir->m_size));
	// Add parentAddress to new struct
	memcpy(
		&readDir->m_parentAddress,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size),
		sizeof(readDir->m_parentAddress));
	// Add ownAddress to new struct
	memcpy(
		&readDir->m_ownAddress,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size),
		sizeof(readDir->m_ownAddress));
	// Deserializes and allocates iBlock
	readDir->m_iBlock = loadIBlock(readDir->m_ownAddress);

	return readDir;
}

// Loads root directory
DirEntry* loadRoot()
{
	// Reads from disk
	DirEntry* root = NULL;

	// Load from disk
	root = loadDirEntry(ROOT_ADDRESS);

	return root;
}

// Load direntry from blockAddress
DirEntry* loadDirEntry(unsigned short blockAddress)
{
	// Loaded direntry
	DirEntry* loadedDirEntry = NULL;

	// Block read
	unsigned char* pBuffer = readBlock(blockAddress);

	// If buffer is valid
	if (pBuffer != NULL)
	{
		loadedDirEntry = deserialize_DirEntry(pBuffer);
	}

	return loadedDirEntry;
}

// Saves DirEntry to block address (own address)
void saveDirEntry(DirEntry* dirent)
{
	unsigned char* pBuffer = NULL;

	serialize_DirEntry(dirent, pBuffer);

	if (pBuffer != NULL)
	{
		writeBlock(dirent->m_ownAddress, pBuffer);
	}
}

// Create DirEntry (assigns a free block)
DirEntry* createDirEntry(char* name, char type, DirEntry* parent)
{
	// Created dir
	DirEntry* createdDirEnt = NULL;

	// If received info is ok
	if ((name != NULL) && ((type == 0x01) || (type == 0x02)) && (parent != NULL))
	{
		// Allocate disk
		unsigned short blockAddress = allocBlock();
		// If address is valid
		if (blockAddress != (gp_superblock->m_bitmapSize + 1))
		{
			createdDirEnt = calloc(1, sizeof(DirEntry));
			strcpy(createdDirEnt->m_name, name);
			createdDirEnt->m_filetype = type;
			createdDirEnt->m_ownAddress = blockAddress;
			createdDirEnt->m_parentAddress = parent->m_ownAddress;
		}
	}
	// Creating root dir
	else if ((name != NULL) && ((type == 0x01) || (type == 0x02)) && (parent == NULL))
	{
		unsigned short blockAddress = allocBlock();
		// If address is valid
		if (blockAddress != (gp_superblock->m_bitmapSize + 1))
		{
			createdDirEnt = calloc(1, sizeof(DirEntry));
			strcpy(createdDirEnt->m_name, name);
			createdDirEnt->m_filetype = type;
			createdDirEnt->m_ownAddress = blockAddress;
			createdDirEnt->m_parentAddress = 0;
		}
	}

	// If created successfully
	if (createdDirEnt != NULL)
	{
		// Save to disk
		saveDirEntry(createdDirEnt);
	}

	return createdDirEnt;
}

// Adds dirEntSrc entry to iBlock of dirEntDst (and create it if not already initialized)
TBool addToIBlock(DirEntry* dirEntDst, DirEntry* dirEntSrc)
{
	// Operation result
	TBool result = false;

	// If both inputs are ok
	if ((dirEntSrc != NULL) && (dirEntDst != NULL))
	{
		// If dirEntDst has no allocated iblock
		if (dirEntDst->m_iBlock == NULL)
		{
			// Initialize iblock
			dirEntDst = initializeIBlock(10);
		}

		// If successfully initialized
		if (dirEntDst->m_iBlock != NULL)
		{
			// Add dir entry to iBlock
			if (addDirEntryToIBlock(dirEntDst->m_iBlock, dirEntSrc))
			{
				result = true;
			}
		}
	}

	return result;
}

// Adds dirEntSrc to iBlock (resize if needed)
TBool addDirEntryToIBlock(iBlock* iblock, DirEntry* dirEntSrc)
{
	// Operation result
	TBool result = false;

	if ((iblock != NULL) && (dirEntSrc != NULL))
	{
		unsigned int idx = 0;
		TBool found = false;
		// Iterates through the iBlock to find empty entry
		while ((idx < iblock->m_size) && (!found))
		{
			// 0 represents free
			if ((iblock->m_contents + idx) == 0)
			{
				found = true;
			}
			else
			{
				idx++;
			}
		}
		// Resize contents if needed
		if (!found)
		{
			// Reallocate bigger memory
			iblock->m_contents = realloc(iblock->m_contents, iblock->m_size + 1);
			iblock->m_size = iblock->m_size + 1;
		}
	}

	return result;
}