#include <string.h>
#include <stdlib.h>
#include "iblock.h"
#include "utils.h"

// Serializes an iBlock to write to disk
// The buffer should have size == 256
void 
serialize_iBlock(iBlock* s_iblock, unsigned char* buffer)
{
	// Add name to buffer
	memcpy(buffer, s_iblock->m_contents, sizeof(s_iblock->m_contents));
}

// Deserializes an iBlock read from disk
// The buffer should have size == 256
iBlock* 
deserialize_iBlock(unsigned char* buffer)
{
	// Returned superblock
	iBlock* psiBlock = malloc(sizeof(iBlock));

	// Add name to buffer
	memcpy(psiBlock->m_contents, buffer, sizeof(psiBlock->m_contents));

	return psiBlock;
}