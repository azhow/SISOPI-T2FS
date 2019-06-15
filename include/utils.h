/*************************************************************************

	Common functions and utilities used by the library.

*************************************************************************/

#ifndef __utils_h__
#define __utils_h__

#include "t2fs.h"
#include "EOperationStatus.h"
#include "TBool.h"

#define DISK_NUM_SECTORS 4000

// Table which contains the open files (max 10 open files simultaneously)
typedef struct {
	DIR2 handles[10];
} OpenFileTable;

// Verifies the validity of a given handle
TBool validateHandle(DIR2 handle);

// Get a valid handle dir entry, used in the readdir2 function, returns the entry read in the pointer
// Assumes a valid handle
EOperationStatus getHandleContent(DIR2 handle, DIRENT2* dirEntry);

// Checks the existence of a given path
TBool exists(char *pathname);

#endif