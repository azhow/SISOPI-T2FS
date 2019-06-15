#include <string.h>
#include <stdlib.h>
#include "superblock.h"
#include "utils.h"

// Serializes the Superblock (MBR) to write to disk
// The buffer should have size == 256
void
serialize_Superblock(Superblock* s_superblock, unsigned char* buffer)
{
	// Memory offset for the Partition Zero
	const unsigned short MBROffsetPartZero = 23;

	// Add name to buffer
	memcpy(buffer + MBROffsetPartZero, &s_superblock->m_sectorsPerBlock, sizeof(s_superblock->m_sectorsPerBlock));

	// Add filetype to buffer
	// Shifts starting position
	memcpy(
		buffer + MBROffsetPartZero + sizeof(s_superblock->m_sectorsPerBlock), 
		&s_superblock->m_rootAddress, 
		sizeof(s_superblock->m_rootAddress));
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

	// Add name to buffer
	memcpy(&psSuperblock->m_sectorsPerBlock, buffer + MBROffsetPartZero, sizeof(psSuperblock->m_sectorsPerBlock));

	// Add filetype to buffer
	// Shifts starting position
	memcpy(
		&psSuperblock->m_rootAddress,
		buffer + MBROffsetPartZero + sizeof(psSuperblock->m_sectorsPerBlock),
		sizeof(psSuperblock->m_rootAddress));

	return psSuperblock;
}