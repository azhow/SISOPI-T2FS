#ifndef __direntry_h__
#define __direntry_h__

#include "EOperationStatus.h"

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct {
	char m_name[32]; // Name of the file
	char m_filetype; // Type of the file (0x01 -> file, 0x02 ->directory)
	unsigned int m_size; // Size in bytes of the file (directories have 0)
	unsigned short m_iBlockAddress; // Sector address of the iBlock
	unsigned short m_parentAddress; // Sector address of the parent DirEntry
	unsigned short m_ownAddress; // Sector address of this DirEntry
	unsigned short m_entries[106]; // Empty
	char m_empty; // Empty (to align)
} DirEntry;

#pragma pack(pop)

// Serializes the DirEntry to write to disk
// The buffer should have size == 256
void serialize_DirEntry(DirEntry* s_dirEntry, unsigned char* buffer);

// Deserializes the DirEntry to read from disk
// The buffer should have size == 256
DirEntry* deserialize_DirEntry(unsigned char* buffer);

#endif