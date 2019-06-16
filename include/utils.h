/*************************************************************************

	Common functions and utilities used by the library.

*************************************************************************/

#ifndef __utils_h__
#define __utils_h__

#include "direntry.h"
#include "t2fs.h"
#include "EOperationStatus.h"
#include "TBool.h"

#define DISK_NUM_SECTORS 4000
#define ROOT_ADDRESS 1

// Definition of the current path (should initialize it rather)
// Current working path
char g_currentPath[32];
DirEntry* gp_currentDirEntry;

// Checks the existence of a given path
DirEntry* exists(char *pathname);

// Searches and returns dirEntry block address of found entry, else 0
// Checks the directory entries of searchDir by comparing its name with the token
unsigned int contains(char* token, DirEntry* searchDir);

// Initializes library
void initialize();

#endif