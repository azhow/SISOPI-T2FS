#include <string.h>
#include <stdlib.h>
#include "TBool.h"
#include "utils.h"
#include "direntry.h"
#include "iblock.h"
#include "apidisk.h"
#include "openfiletable.h"

// Definition of the current path
// Current working path
char g_currentPath[32] = "/";
DirEntry* gp_currentDirEntry = NULL;

// Checks the existence of a given path and assigns the found entry
// Assumes non empty string
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
				// Buffer which contains info from disk
				unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
				if (read_sector(gp_currentDirEntry->m_parentAddress, buffer) == EOpSuccess)
				{
					foundDir = deserialize_DirEntry(buffer);
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
			if (read_sector(ROOT_ADDRESS, buffer) == EOpSuccess)
			{
				foundDir = deserialize_DirEntry(buffer);
			}
			// Free allocated memory
			free(buffer);
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
				// Buffer which contains info from disk
				unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
				// Update dirEntry
				if (read_sector(blockAddOfFound, buffer) == EOpSuccess)
				{
					foundDir = deserialize_DirEntry(buffer);
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
	}
	// Input empty should be root directory, return always the root
	else
	{
		// Buffer which contains info from disk
		unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
		// Update dirEntry
		if (read_sector(ROOT_ADDRESS, buffer) == EOpSuccess)
		{
			foundDir = deserialize_DirEntry(buffer);
		}
		// Free allocated memory
		free(buffer);
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
					// Index of the array (starts at three because its at this index that start the entries)
					unsigned short i = 3;
					// Current content being read
					unsigned int currContent = (unsigned int)(blockToRead->m_contents[i]);
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
						// To avoid infinite loop
						else
						{
							// Increments
							i++;
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

// Initializes library
void
initialize()
{
	// Current path is root
	strcpy(g_currentPath, "/");
	// Buffer which contains info from disk
	unsigned char* buffer = malloc(sizeof(char) * SECTOR_SIZE);
	read_sector(ROOT_ADDRESS, buffer);
	// Current dirEntry of root
	gp_currentDirEntry = deserialize_DirEntry(buffer);
	// Free buffer
	free(buffer);
	// Initializes openfiletable
	gp_openFileTable = calloc(1, sizeof(OpenFileTable));
	// TODO initialize bitmap of free memory
}