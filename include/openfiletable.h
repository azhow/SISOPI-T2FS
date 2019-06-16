#ifndef __openfiletable_h__
#define __openfiletable_h__

#include "direntry.h"
#include "t2fs.h"

// OpenFileStruct
typedef struct 
{
	DirEntry* m_openFileDirEntry; // Dir entry of the open file
	unsigned int m_filepointer; // Pointer inside the file
} OpenFile;

// OpenFileTable struct
typedef struct
{
	OpenFile* m_openFiles[10]; // Array containing the 10 open files
} OpenFileTable;

OpenFileTable* gp_openFileTable;

// Add DirEntry of file to table
DIR2 addOpenFileToTable(DirEntry* fileToOpen);

// Remove entry from table
void removeOpenFileFromTable(unsigned int handle);

#endif