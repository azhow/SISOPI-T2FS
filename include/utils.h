/*************************************************************************

	Common functions and utilities used by the library.

*************************************************************************/

#ifndef __utils_h__
#define __utils_h__

#include "direntry.h"
#include "t2fs.h"
#include "EOperationStatus.h"
#include "TBool.h"

// Checks the existence of a given path
DirEntry* exists(char *pathname);

// Searches and returns dirEntry block address of found entry, else 0
// Checks the directory entries of searchDir by comparing its name with the token
unsigned int contains(char* token, DirEntry* searchDir);

// Initializes library
void initialize();

// Translate block address to corresponding sector
unsigned short BlockAddToSectorAdd(unsigned short blockAddress);

// Reads block with address blockAdd from disk and adds all info read to buffer
// Return has size = secPerBlock * SECTOR_SIZE
unsigned char* readBlock(unsigned short blockAddress);

// Writes info from pBuffer to block with address blockAdd
// pBuffer must have size = secPerBlock * SECTOR_SIZE
void writeBlock(unsigned short blockAddress, unsigned char* pBuffer);

#endif