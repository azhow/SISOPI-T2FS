#include "bitmap.h"
#include "apidisk.h"
#include "superblock.h"
#include "TBool.h"
#include <stdlib.h>
#include <string.h>

// Bitmap of the disk
Bitmap* gp_memBitmap = NULL;

// Get the index of the first free block (return superblock->m_bitmapSize + 1 if not found)
unsigned short getFreeBlock()
{
	// Returned value
	unsigned short blockIndex = 0;

	// Current block being searched
	char currBlock = gp_memBitmap->m_map[0];

	// Signals the end of the search (no free block found)
	TBool endOfBitmap = false;

	// The char "0" (0x30) represents allocated (to not be confused with \0) and char "1" free
	while ((currBlock != 0x31) && (!endOfBitmap))
	{
		// If the current block is inside the bitmap
		if (blockIndex <= gp_superblock->m_bitmapSize)
		{
			// Update info
			blockIndex++;
			currBlock = gp_memBitmap->m_map[blockIndex];
		}
		else
		{
			// Got to the end of the bitmap
			endOfBitmap = true;
		}
	}

	return blockIndex;
}

// Serializes the Bitmap to write to disk
// The buffer should have size == 4000
void serialize_Bitmap(Bitmap* s_bitmap, unsigned char* buffer)
{
	// Add map to buffer
	memcpy(buffer, s_bitmap->m_map, sizeof(s_bitmap->m_map));
}

// Deserializes the Bitmap to read from disk
// The buffer should have size == 4000
Bitmap* deserialize_Bitmap(unsigned char* buffer)
{
	// Returned Bitmap (should initialize with zeroes
	Bitmap* psBitmap = calloc(1, sizeof(Bitmap));

	// Add buffer to map
	memcpy(psBitmap->m_map, buffer, sizeof(psBitmap->m_map));

	return psBitmap;
}

// Saves global bitmap to disk
void saveBitmap()
{
	// Allocates buffer for the bitmap
	unsigned char* buffer = calloc(1, sizeof(Bitmap));

	// Serialize bitmap
	serialize_Bitmap(gp_memBitmap, buffer);

	// Sector number
	unsigned short idx;

	// Save sector by sector (starting from sector 1 through 17 -> 4000/256)
	for (idx = 1; idx < 17; idx++)
	{
		// Write sector should offset the buffer
		write_sector(idx, buffer + ((idx-1) * SECTOR_SIZE));
	}

	free(buffer);
}

// Loads bitmap from disk to global
void loadBitmap()
{
	// Allocates buffer for the bitmap
	// Get size of 16 sectors
	unsigned char* buffer = calloc(1, 16*SECTOR_SIZE);

	// Sector number
	unsigned short idx;

	// Save sector by sector (starting from sector 1 through 17 -> 4000/256)
	for (idx = 1; idx < 17; idx++)
	{
		// Write sector should offset the buffer
		read_sector(idx, buffer + ((idx - 1) * SECTOR_SIZE));
	}

	// Deserialize bitmap (the function ignores the extra bytes)
	gp_memBitmap = deserialize_Bitmap(buffer);

	free(buffer);
}

// Assigns and allocate the returned block (saves to disk)
unsigned short allocBlock()
{
	// Return value
	unsigned short retValue = getFreeBlock();
	
	// If was able to find a free block
	if (retValue != gp_superblock->m_bitmapSize + 1)
	{
		// Set to "0"
		gp_memBitmap->m_map[retValue] = 0x30;
		// Save to disk
		saveBitmap();
	}

	return retValue;
}

// Free a block (saves to disk)
void freeBlock(unsigned short block)
{
	// If block index is valid
	if (block < gp_superblock->m_bitmapSize)
	{
		// Set the value to "1"
		gp_memBitmap->m_map[block] = 0x31;
		// Save to disk
		saveBitmap();
	}
}