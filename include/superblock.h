#ifndef __superblock_h__
#define __superblock_h__

#define MBR_SECTOR 0

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct
{
	int m_sectorsPerBlock; // Number of sectors per data block
	unsigned short m_rootAddress; // Address of the sector of the root directory
	unsigned short m_bitmapSize; // Size in bytes of the bitmap
} Superblock;

#pragma pack(pop)

// Global information of the superblock
Superblock* gp_superblock;

// Serializes the Superblock (MBR) to write to disk
// The buffer should have size == 256
void serialize_Superblock(Superblock* s_superblock, unsigned char* buffer);

// Deserializes the Superblock to read from disk
// The buffer should have size == 256
Superblock* deserialize_Superblock(unsigned char* buffer);

#endif