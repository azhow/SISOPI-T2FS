#ifndef __superblock_h__
#define __superblock_h__

#define MBR_SECTOR 0
// Root block address
#define ROOT_ADDRESS 0
// The first block starts at sector 17
#define FIRST_BLOCK_SECTOR 17
// Maximum number of sectors
#define SECTORS_TOTAL 4000

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct
{
	int m_sectorsPerBlock; // Number of sectors per data block
	unsigned short m_rootAddress; // Address of the block of the root directory
	unsigned short m_bitmapSize; // Size in bytes of the bitmap
} Superblock;

#pragma pack(pop)

// Global information of the superblock
Superblock* gp_superblock;

// Save superblock to disk
void saveSuperblock();

// Load superblock from disk (into the the global variable)
Superblock* loadSuperblock();

// Initializes superblock saves to disk and returns the pointer of the allocated struct
void initializeSuperblock(int secPerBlock);

#endif