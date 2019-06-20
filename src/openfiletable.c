#include "openfiletable.h"
#include "TBool.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

OpenFileTable* gp_openFileTable = NULL;

// Get the first free handle in gp_OpenFileTable, returns -1 if none is available
int
getFreeHandle()
{
	// Return value
	int freeHandle = -1;
	// Used inside the loop
	unsigned int i = 0;
	// Found empty entry?
	TBool found = false;
	// Iterates through the table
	while ((!found) && (i < 10))
	{
		if (gp_openFileTable->m_openFiles[i] == NULL)
		{
			// Set free handle to available entry
			freeHandle = i;
			found = true;
		}
		else
		{
			i++;
		}
	}

	return freeHandle;
}

// Creates new open file
OpenFile*
createOpenFile(DirEntry* fileToOpen)
{
	// Return value
	OpenFile* newEntry = NULL;

	newEntry = malloc(sizeof(OpenFile));
	// Copy entry
	newEntry->m_openFileDirEntry = calloc(1, sizeof(DirEntry));
	strcpy(newEntry->m_openFileDirEntry->m_name, fileToOpen->m_name);
	newEntry->m_openFileDirEntry->m_filetype = fileToOpen->m_filetype;
	newEntry->m_openFileDirEntry->m_size = fileToOpen->m_size;
	newEntry->m_openFileDirEntry->m_iBlock = fileToOpen->m_iBlock;
	newEntry->m_openFileDirEntry->m_ownAddress = fileToOpen->m_ownAddress;
	newEntry->m_openFileDirEntry->m_parentAddress = fileToOpen->m_parentAddress;
	// Initializes file pointer to first byte of the file
	newEntry->m_filepointer = 0;

	return newEntry;
}

// Add DirEntry of file to table, returns where it was inserted
DIR2
addOpenFileToTable(DirEntry* fileToOpen)
{
	// Return value
	DIR2 handle = -1;

	// If valid value
	if (fileToOpen != NULL)
	{
		// Gets free handle in the table
		int freeHandle = getFreeHandle();
		// If the handle is valid
		if(freeHandle != -1)
		{
			// Assign to table
			gp_openFileTable->m_openFiles[freeHandle] = createOpenFile(fileToOpen);
			// Operation successfull
			handle = freeHandle;
		}
	}

	return handle;
}

// Remove entry from table
void
removeOpenFileFromTable(unsigned int handle)
{
	// If entry has content
	if (gp_openFileTable->m_openFiles[handle] != NULL)
	{
		// Free memory
		free((((OpenFile*)gp_openFileTable->m_openFiles[handle])->m_openFileDirEntry));
		// Set entry to null
		gp_openFileTable->m_openFiles[handle] = NULL;
	}
}