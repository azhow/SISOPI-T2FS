#include <string.h>
#include <stdlib.h>
#include "TBool.h"
#include "utils.h"
#include "direntry.h"
#include "superblock.h"
#include "bitmap.h"
#include "iblock.h"
#include "apidisk.h"
#include "openfiletable.h"

// Checks the existence of a given path and assigns the found entry
// Assumes non empty string
// Returns null if not found
DirEntry*
exists(char *pathname)
{
	// DirEntry to start search
	DirEntry* foundDir = NULL;

	// Path delimiter
	char delimiter[2] = "/";

	// Intermediate string to avoid modifying the input
	char* intString = calloc(strlen(pathname) + 1, sizeof(char));

	strcpy(intString, pathname);

	// Tokenize
	char* token = strtok(intString, delimiter);

	// Non empty string
	if (token != NULL)
	{
		// Process the first char
		// If from current dir
		if ((strlen(token) == 1) && (strncmp(token, ".", 1) == 0))
		{
			// Process from current path
			foundDir = gp_currentDirEntry;
		}
		// else if from parent dir
		else if ((strlen(token) == 2) && (strncmp(token, "..", 2) == 0))
		{
			// Process from current path parent
			// Must be a valid address
			if (gp_currentDirEntry->m_parentAddress != 0)
			{
				foundDir = loadDirEntry(gp_currentDirEntry->m_parentAddress);
			}
		}
		// Absolute path
		else
		{
			foundDir = loadRoot();
		}

		// Does the current dir exists?
		TBool currDirExists = true;

		// Transverse
		while ((token != NULL) && currDirExists)
		{
			// Searches and returns dirEntry block address of found entry, else 0
			unsigned int blockAddOfFound = contains(token, foundDir);
			// If found
			if (blockAddOfFound != 0)
			{
				foundDir = loadDirEntry(blockAddOfFound);
				// Updates currDir value
				currDirExists = true;
			}
			// Not found
			else
			{
				// currDir not found
				currDirExists = false;
			}
			token = strtok(NULL, delimiter);
		}
		// If not found, should return null
		if (!currDirExists)
		{
			foundDir = NULL;
		}
	}
	// Input empty should be root directory, return always the root
	else
	{
		foundDir = loadRoot();
	}

	return foundDir;
}

// Searches and returns dirEntry block address of found entry, else 0
unsigned int
contains(char* token, DirEntry* searchDir)
{
	// Address of iblock of the element found (if found)
	unsigned int iBlockOfFound = 0;

	// If valid search directory
	if (searchDir != NULL)
	{
		// If filetype is directory
		if (searchDir->m_filetype == 0x02)
		{
			// iBlock being read
			iBlock* blockToRead = loadIBlock(searchDir->m_ownAddress);
			// If loaded correctly
			if (blockToRead != NULL)
			{
				// Index of the array (starts at three because its at this index that start the entries)
				unsigned short i = 3;
				// Current content being read (block address)
				unsigned int currContent = (unsigned int)(blockToRead->m_contents[i]);
				// Found value?
				TBool found = false;
				// While not found and valid value and in bound value
				while ((currContent != 0) && (!found) && (i < (gp_superblock->m_sectorsPerBlock * SECTOR_SIZE)))
				{
					// Loads dir entry
					DirEntry* currDirEntry = loadDirEntry(currContent);
					// Compares the name
					if (strncmp(token, currDirEntry->m_name, sizeof(currDirEntry->m_name)) == 0)
					{
						iBlockOfFound = currDirEntry->m_ownAddress;
						// Found
						found = true;
					}
					// Else, we shuold look the next entry in the content
					else
					{
						// Increments
						i++;
						// Updates current content
						currContent = (unsigned int)(blockToRead->m_contents[i]);
					}
					// Free alocated memory
					free(currDirEntry);
				}
			}
		}
	}

	return iBlockOfFound;
}

// Initializes library
void
initialize()
{
	// Initialize superblock (read from disk)
	gp_superblock = loadSuperblock();
	// Load root dir
	gp_currentDirEntry = loadRoot();
	// Initializes openfiletable
	gp_openFileTable = malloc(sizeof(OpenFileTable));
	// Initialize bitmap of free memory
	loadBitmap();
}

// Translate block address to corresponding sector
// Returns 0 if it does not exists
unsigned short BlockAddToSectorAdd(unsigned short blockAddress)
{
	return ((((blockAddress * gp_superblock->m_sectorsPerBlock) + FIRST_BLOCK_SECTOR) < SECTORS_TOTAL)) ?
		(blockAddress * gp_superblock->m_sectorsPerBlock) + FIRST_BLOCK_SECTOR :
		0;
}

// Reads block with address blockAdd from disk and adds all info read to buffer
// Return has size = secPerBlock * SECTOR_SIZE
unsigned char* readBlock(unsigned short blockAddress)
{
	// Buffer to save information
	unsigned char* pBuffer = NULL;

	// Sector address
	unsigned short sectorAdd = BlockAddToSectorAdd(blockAddress);

	// If sector address is valid, we read sector
	if (sectorAdd > 0)
	{
		pBuffer = malloc(SECTOR_SIZE * gp_superblock->m_sectorsPerBlock);

		// Read the info from all sectors
		unsigned short i;
		for (i = 0; i < gp_superblock->m_sectorsPerBlock; i++)
		{
			read_sector(sectorAdd + i, pBuffer + (i * SECTOR_SIZE));
		}
	}

	return pBuffer;
}

// Writes info from pBuffer to block with address blockAdd
// pBuffer must have size = secPerBlock * SECTOR_SIZE
void writeBlock(unsigned short blockAddress, unsigned char* pBuffer)
{
	// Sector address
	unsigned short sectorAdd = BlockAddToSectorAdd(blockAddress);

	// If sector address is valid, we read sector
	if ((sectorAdd > 0) && (pBuffer != NULL))
	{
		// Read the info from all sectors
		unsigned short i;
		for (i = 0; i < gp_superblock->m_sectorsPerBlock; i++)
		{
			write_sector(sectorAdd + i, pBuffer + (i * SECTOR_SIZE));
		}
	}
}