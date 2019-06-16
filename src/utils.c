#include <string.h>
#include <stdlib.h>
#include "TBool.h"
#include "utils.h"
#include "direntry.h"
#include "iblock.h"
#include "apidisk.h"

// Definition of the current path (should initialize it rather)
// Current working path
char g_currentPath[32];
DirEntry* g_currentDirEntry;
unsigned int g_rootAddress = 1;

#include <stdio.h>

// Checks the existence of a given path
TBool 
exists(char *pathname)
{
	// Return of the operation
	TBool result = false;
	// Path delimiter
	char delimiter[2] = "/";

	// Tokenize
	char* token = strtok(pathname, delimiter);

	// Non empty string
	if (token != NULL)
	{
		// DirEntry to start search
		DirEntry* searchDir = NULL;

		// Process the first char
		// If from current dir
		if ((strlen(token) == 1) && (strncmp(token, ".", 1) == 0))
		{
			// Process from current path
			searchDir = g_currentDirEntry;
		}
		// else if from parent dir
		else if ((strlen(token) == 2) && (strncmp(token, "..", 2) == 0))
		{
			// Process from current path parent
			// Must be a valid address
			if (g_currentDirEntry->m_parentAddress != 0)
			{
				// Buffer which contains info from disk
				unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
				if (read_sector(g_currentDirEntry->m_parentAddress, buffer) == EOpSuccess)
				{
					searchDir = deserialize_DirEntry(buffer);
				}
				// Free allocated memory
				free(buffer);
			}
		}
		// Absolute path
		else
		{
			// Process from root
			// Buffer which contains info from disk
			unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
			if (read_sector(g_rootAddress, buffer) == EOpSuccess)
			{
				searchDir = deserialize_DirEntry(buffer);
			}
			// Free allocated memory
			free(buffer);
		}

		// Does the current dir exists?
		TBool currDirExists = false;

		// Transverse
		while ((token != NULL) && currDirExists)
		{
			// Searches and returns dirEntry block address of found entry, else 0
			unsigned int blockAddOfFound = contains(token, searchDir);
			// If found
			if (blockAddOfFound != 0)
			{
				// Buffer which contains info from disk
				unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
				// Update dirEntry
				if (read_sector(blockAddOfFound, buffer) == EOpSuccess)
				{
					searchDir = deserialize_DirEntry(buffer);
				}
				// Free allocated memory
				free(buffer);
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

		result = currDirExists;
	}
	// Might be root directory?
	else
	{
		// TODO
	}

	return result;
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
			iBlock* blockToRead = NULL;
			// Buffer which contains info from disk
			unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
			// Update dirEntry
			if (read_sector(searchDir->m_iBlockAddress, buffer) == EOpSuccess)
			{
				blockToRead = deserialize_iBlock(buffer);
				// If deserialized correctly
				if (blockToRead != NULL)
				{
					// Index of the array
					unsigned short i = 0;
					// Current content being read
					unsigned int currContent = (unsigned int)(blockToRead->m_contents);
					// Found value?
					TBool found = false;
					// While not found and valid value and in bound value
					while ((currContent != 0) && (!found) && (i <= 128))
					{
						// Clears buffer
						memset(buffer, 0, sizeof(char) * SECTOR_SIZE);
						// Update dirEntry
						if (read_sector(currContent, buffer) == EOpSuccess)
						{
							DirEntry* currDirEntry = deserialize_DirEntry(buffer);
							// Checks the name of the content
							// If the name matches the token, then the result is found
							if (strncmp(token, currDirEntry->m_name, sizeof(currDirEntry->m_name)) == 0)
							{
								iBlockOfFound = currDirEntry->m_ownAddress;
							}
							// Else, we shuold look the next entry in the content
							else
							{
								// Increments
								i++;
								// Updates current content
								currContent = (unsigned int)(blockToRead->m_contents + i);
							}
						}
					}
				}
			}
			// Free memory
			free(buffer);
		}
	}

	return iBlockOfFound;
}