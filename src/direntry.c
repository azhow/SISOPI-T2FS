#include "direntry.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// Serializes the DirEntry to write to disk
// The buffer should have size == 256
void
serialize_DirEntry(DirEntry* s_dirEntry, unsigned char* buffer)
{
	// Temp buffer
	unsigned char* tempBuffer = calloc(SECTOR_SIZE, sizeof(unsigned char));
	// Add name to temp buffer
	memcpy(tempBuffer, s_dirEntry->m_name, sizeof(s_dirEntry->m_name));
	// Add filetype to temp buffer
	// Shifts starting position
	memcpy(tempBuffer + sizeof(s_dirEntry->m_name), &s_dirEntry->m_filetype, sizeof(s_dirEntry->m_filetype));
	// Add size to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype),
		&s_dirEntry->m_size, 
		sizeof(s_dirEntry->m_size));
	// Add iBlockAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size),
		&s_dirEntry->m_iBlockAddress, 
		sizeof(s_dirEntry->m_iBlockAddress));
	// Add parentAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress),
		&s_dirEntry->m_parentAddress, 
		sizeof(s_dirEntry->m_parentAddress));
	// Add ownAddress to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*2,
		&s_dirEntry->m_ownAddress, 
		sizeof(s_dirEntry->m_ownAddress));
	// Add entries to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*3,
		&s_dirEntry->m_entries, 
		sizeof(s_dirEntry->m_entries));
	// Add empty to temp buffer
	memcpy(
		tempBuffer + sizeof(s_dirEntry->m_name) + sizeof(s_dirEntry->m_filetype) + sizeof(s_dirEntry->m_size) + sizeof(s_dirEntry->m_iBlockAddress)*3  + sizeof(s_dirEntry->m_entries),
		&s_dirEntry->m_empty, 
		sizeof(s_dirEntry->m_empty));

	memcpy(buffer, tempBuffer, sizeof(DirEntry));
}

// Deserializes the DirEntry to read from disk
// The buffer should have size == 256
DirEntry* 
deserialize_DirEntry(unsigned char* buffer)
{
	// Returned read dir
	DirEntry* readDir = malloc(sizeof(DirEntry));

	// Add name to new struct
	memcpy(readDir->m_name, buffer, sizeof(readDir->m_name));
	// Add filetype to new struct
	// Shifts starting position
	memcpy(&readDir->m_filetype, buffer + sizeof(readDir->m_name), sizeof(readDir->m_filetype));
	// Add size to new struct
	memcpy(
		&readDir->m_size,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype),
		sizeof(readDir->m_size));
	// Add iBlockAddress to new struct
	memcpy(
		&readDir->m_iBlockAddress,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size),
		sizeof(readDir->m_iBlockAddress));
	// Add parentAddress to new struct
	memcpy(
		&readDir->m_parentAddress,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size) + sizeof(readDir->m_iBlockAddress),
		sizeof(readDir->m_parentAddress));
	// Add ownAddress to new struct
	memcpy(
		&readDir->m_ownAddress,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size) + sizeof(readDir->m_iBlockAddress) * 2,
		sizeof(readDir->m_ownAddress));
	// Add entries to new struct
	memcpy(
		readDir->m_entries,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size) + sizeof(readDir->m_iBlockAddress) * 3,
		sizeof(readDir->m_entries));
	// Add empty to new struct
	memcpy(
		&readDir->m_empty,
		buffer + sizeof(readDir->m_name) + sizeof(readDir->m_filetype) + sizeof(readDir->m_size) + sizeof(readDir->m_iBlockAddress) * 3 + sizeof(readDir->m_entries),
		sizeof(readDir->m_empty));

	return readDir;
}