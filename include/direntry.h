#ifndef __direntry_h__
#define __direntry_h__

#include "iblock.h"
#include "TBool.h"

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct {
	char m_name[32]; // Name of the file
	char m_filetype; // Type of the file (0x01 -> file, 0x02 ->directory)
	unsigned int m_size; // Size in bytes of the file (directories have 0)
	unsigned short m_parentAddress; // Block address of the parent DirEntry
	unsigned short m_ownAddress; // Sector address of this DirEntry
	iBlock* m_iBlock; // Block address of the iBlock
} DirEntry;

#pragma pack(pop)

// global of current dir entry
DirEntry* gp_currentDirEntry;

// Loads root directory
DirEntry* loadRoot();

// Create DirEntry (assigns a free block) and saves to disk if successfull
DirEntry* createDirEntry(char* name, char type, DirEntry* parent);

// Load direntry from blockAddress
DirEntry* loadDirEntry(unsigned short blockAddress);

// Saves DirEntry to block address (own address)
TBool saveDirEntry(DirEntry* dirent);

// Adds dirEntSrc to iBlock (resize if needed)
TBool addDirEntryToIBlock(iBlock* iblock, DirEntry* dirEntSrc);

// Adds dirEntSrc entry to iBlock of dirEntDst (and create it if not already initialized)
TBool addToIBlock(DirEntry* dirEntDst, DirEntry* dirEntSrc);

#endif