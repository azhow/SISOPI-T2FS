#include <string.h>
#include <stdlib.h>
#include "iblock.h"
#include "utils.h"
#include "superblock.h"
#include "bitmap.h"

// Serializes an iBlock to write to disk
// The buffer should have size of a block
// Return signals the need for another block
// Return 0 no need for another block
unsigned short 
serialize_iBlock(iBlock* s_iblock, unsigned char* buffer, unsigned int startOffset, unsigned int bufferOffset)
{
	// Add of next block
	unsigned short nextBlockAdd = 0;

	// Need for another block
	// If the size of iblock is bigger than block size
	TBool needAnotherBlock = (sizeof(unsigned short) * s_iblock->m_size) > (gp_superblock->m_sectorsPerBlock * SECTOR_SIZE);

	// If valid address and need another block, we need to set the next block position
	if (needAnotherBlock)
	{
		nextBlockAdd = getFreeBlock();
		// If found free block successfully
		if (nextBlockAdd < gp_superblock->m_bitmapSize + 1)
		{
			// Set content[0] to the address
			memset(buffer + bufferOffset, nextBlockAdd, sizeof(unsigned short));
			// Add +1 to buffer size
			bufferOffset++;
		}
	}

	// Copy info to buffer
	memcpy(buffer + bufferOffset, s_iblock->m_contents + startOffset, (gp_superblock->m_sectorsPerBlock * SECTOR_SIZE) - bufferOffset);

	return nextBlockAdd;
}

// Deserializes an iBlock read from disk
// The buffer should have size of a block
iBlock* 
deserialize_iBlock(unsigned char* buffer, unsigned int offset)
{
	// Returned superblock
	iBlock* psiBlock = malloc(sizeof(iBlock));
	// Initialize size
	psiBlock->m_size = 0;

	unsigned int i = 0;
	while ((psiBlock->m_size + offset + i) < 4000)
	{
		// Copy content from buffer
		memcpy(psiBlock->m_contents, buffer + offset + i, sizeof(unsigned short));
		i++;
		psiBlock->m_size++;
	}

	return psiBlock;
}

// Initialize iBlock
iBlock* initializeIBlock(unsigned int size)
{
	iBlock* retValue = calloc(1, sizeof(iBlock));

	retValue->m_size = size;
	retValue->m_contents = calloc(retValue->m_size, sizeof(unsigned short));

	return retValue;
}

// Concatenates the currBlock in the loadedIBlock
void concatenateIBlock(iBlock* loadedIBlock, iBlock* currBlock)
{
	// Zero the continuation
	loadedIBlock->m_contents[0] = 0;
	// Resize memory
	loadedIBlock->m_contents = realloc(loadedIBlock->m_contents, sizeof(unsigned short)*(loadedIBlock->m_size + currBlock->m_size - 1));
	// Copy memory
	memcpy(loadedIBlock->m_contents + (sizeof(unsigned short)*loadedIBlock->m_size), currBlock->m_contents + 1, sizeof(unsigned short) * currBlock->m_size);
}

// Should load iBlock from disk from the same block as a dirEntry
iBlock* loadIBlock(unsigned short blockAdd)
{
	// Offset inside the buffer considering dirEntry data
	const unsigned int cOffsetDirEntryData = 41;

	iBlock* loadedIBlock = NULL;

	unsigned char* pBuffer = readBlock(blockAdd);

	// Deserializes the read info
	loadedIBlock = deserialize_iBlock(pBuffer, cOffsetDirEntryData);
	
	// If has continuation record, must load it
	if (loadedIBlock->m_contents[0] != 0)
	{
		pBuffer = readBlock(loadedIBlock->m_contents[0]);
		iBlock* currBlock = deserialize_iBlock(pBuffer, 0);
		TBool end = false;
		do
		{
			// Concatenate with the loadediBlock
			concatenateIBlock(loadedIBlock, currBlock);
			// Read new block
			pBuffer = readBlock(currBlock->m_contents[0]);
			free(currBlock);
			// Deserialize it
			currBlock = deserialize_iBlock(pBuffer, 0);
			// Load last block
			if ((currBlock->m_contents[0] == 0))
			{
				// Concatenate with the loadediBlock
				concatenateIBlock(loadedIBlock, currBlock);
				free(currBlock);
				end = true;
			}
		} while (!end);
	}
	free(pBuffer);

	return loadedIBlock;
}