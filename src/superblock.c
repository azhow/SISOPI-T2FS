#include <string.h>
#include <stdlib.h>
#include "superblock.h"
#include "utils.h"

// Global information of the superblock
Superblock* gp_superblock = NULL;

// Serializes the Superblock (MBR) to write to disk
// The buffer should have size == 256
void
serialize_Superblock(Superblock* s_superblock, unsigned char* buffer)
{
	// Memory offset for the Partition Zero
	const unsigned short MBROffsetPartZero = 23;

	// Add sectors per block to buffer
	memcpy(buffer + MBROffsetPartZero, &s_superblock->m_sectorsPerBlock, sizeof(s_superblock->m_sectorsPerBlock));

	// Add root address to buffer
	// Shifts starting position
	memcpy(
		buffer + MBROffsetPartZero + sizeof(s_superblock->m_sectorsPerBlock), 
		&s_superblock->m_rootAddress, 
		sizeof(s_superblock->m_rootAddress));

	// Add bitmap size to buffer
	// Shifts starting position
	memcpy(
		buffer + MBROffsetPartZero + sizeof(s_superblock->m_sectorsPerBlock) + sizeof(s_superblock->m_rootAddress),
		&s_superblock->m_bitmapSize,
		sizeof(s_superblock->m_bitmapSize));
}

// Deserializes the Superblock to read from disk
// The buffer should have size == 256
Superblock* 
deserialize_Superblock(unsigned char* buffer)
{
	// Returned superblock
	Superblock* psSuperblock = malloc(sizeof(Superblock));

	// Memory offset for the Partition Zero
	const unsigned short MBROffsetPartZero = 23;

	// Add sectorsPerBlock to buffer
	memcpy(&psSuperblock->m_sectorsPerBlock, buffer + MBROffsetPartZero, sizeof(psSuperblock->m_sectorsPerBlock));

	// Add rootAddress to buffer
	// Shifts starting position
	memcpy(
		&psSuperblock->m_rootAddress,
		buffer + MBROffsetPartZero + sizeof(psSuperblock->m_sectorsPerBlock),
		sizeof(psSuperblock->m_rootAddress));

	// Add bitmap size to buffer
	memcpy(
		&psSuperblock->m_bitmapSize,
		buffer + MBROffsetPartZero + sizeof(psSuperblock->m_sectorsPerBlock) + sizeof(psSuperblock->m_rootAddress),
		sizeof(psSuperblock->m_bitmapSize));

	return psSuperblock;
}