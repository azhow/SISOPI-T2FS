#ifndef __bitmap_h__
#define __bitmap_h__

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size
#pragma pack(push, 1)

// Bitmap of memory blocks, will use 16 sectors
typedef struct
{
	char m_map[4000]; // The map itself, already has the biggest size possible (we use the m_size from the superblock to size it properly)
} Bitmap;

#pragma pack(pop)

// Bitmap of the disk
Bitmap* gp_memBitmap;

// Saves global bitmap to disk
void saveBitmap();

// Loads bitmap from disk to global
void loadBitmap();

// Assigns and allocate the returned block (saves to disk)
unsigned short allocBlock();

// Free a block (saves to disk)
void freeBlock(unsigned short idx);

#endif