#include <string.h>
#include <stdlib.h>
#include "superblock.h"
#include "apidisk.h"
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

// Save superblock to disk
void saveSuperblock()
{
	// Buffer for the superblock
	unsigned char* pBuffer = calloc(SECTOR_SIZE, sizeof(char));

	// Read sector MBR_SECTOR
	// MUST preserve the old contents
	if (read_sector(MBR_SECTOR, pBuffer) == EOpSuccess)
	{
		// Serializes the superblock
		serialize_Superblock(gp_superblock, pBuffer);
		// Write sector
		write_sector(MBR_SECTOR, pBuffer);
	}

	free(pBuffer);
}

// Load superblock from disk (into the the global variable)
Superblock* loadSuperblock()
{
	Superblock* psSuperblock = NULL;

	// Buffer for the superblock
	unsigned char* pBuffer = calloc(SECTOR_SIZE, sizeof(char));

	// Read sector MBR_SECTOR
	// MUST preserve the old contents
	if (read_sector(MBR_SECTOR, pBuffer) == EOpSuccess)
	{
		// Serializes the superblock
		psSuperblock = deserialize_Superblock(pBuffer);
	}

	free(pBuffer);

	return psSuperblock;
}

// Initializes superblock saves to disk and returns the pointer of the allocated struct
void initializeSuperblock(int secPerBlock)
{
	// Superblock struct
	Superblock* psSuperblock = malloc(sizeof(Superblock));
	psSuperblock->m_sectorsPerBlock = secPerBlock;
	psSuperblock->m_rootAddress = FIRST_BLOCK_SECTOR;
	// Total number of sectors in the disk - MBR - BITMAPsectors
	const unsigned short cNumOfSectors = 4000 - 1 - 16;
	// Number of blocks in the map (take the lowest integer from the division this results in wasted space in the disk)
	psSuperblock->m_bitmapSize = cNumOfSectors / secPerBlock;
	
	// Free memory if already initialized
	if (gp_superblock != NULL)
	{
		free(gp_superblock);
	}
	// Asssign global
	gp_superblock = psSuperblock;

	// Save to disk
	saveSuperblock();
}