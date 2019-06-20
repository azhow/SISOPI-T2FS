#include <string.h>
#include <stdlib.h>
#include "iblock.h"
#include "utils.h"
#include "superblock.h"

// Serializes an iBlock to write to disk
// The buffer should have size of a block
void 
serialize_iBlock(iBlock* s_iblock, unsigned char* buffer)
{
	// Add name to buffer
	memcpy(buffer, s_iblock->m_contents, sizeof(unsigned short) * s_iblock->m_size);
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
	while ((buffer + offset + i) < 4000)
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