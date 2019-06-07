/*************************************************************************

	Common functions and utilities used by the library.

*************************************************************************/

#ifndef __utils_h__
#define __utils_h__

#include "t2fs.h"
#include "EOperationStatus.h"
#include "TBool.h"

#define DISK_NUM_SECTORS 4000

// Verifies the validity of a given handle
TBool validadeHandle(DIR2 handle);

// Get a valid handle dir entry, used in the readdir2 function, returns the entry read in the pointer
// Assumes a valid handle
EOperationStatus getHandleContent(DIR2 handle, DIRENT2* dirEntry);

#endif