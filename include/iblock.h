#ifndef __iblock_h__
#define __iblock_h__

#include "TBool.h"

typedef struct
{
	unsigned int m_size; // Number of contents
	unsigned short* m_contents; // Addresses contained in the contents
} iBlock;

// Initialize iBlock
iBlock* initializeIBlock(unsigned int size);

// Should load iBlock from disk from the same block as a dirEntry
// Returns an iblock which contains all other iblocks
iBlock* loadIBlock(unsigned short blockAdd);

// Serializes an iBlock to write to disk
void serialize_iBlock(iBlock* s_iblock, unsigned char* buffer);

#endif