#ifndef __direntry_h__
#define __direntry_h__

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct {
	char m_name[32]; // Name of the file
	char m_filetype; // Type of the file (0x01 -> file, 0x02 ->directory)
	unsigned int m_size; // Size in bytes of the file (directories have 0)
	unsigned short m_iBlockAddress; // Block address of the iBlock
	unsigned short m_parentAddress; // Block address of the parent DirEntry
	unsigned short m_ownAddress; // Sector address of this DirEntry
	unsigned short m_entries[106]; // Empty
	char m_empty; // Empty (to align)
} DirEntry;

#pragma pack(pop)

// global of current dir entry
DirEntry* gp_currentDirEntry;

// Loads root directory
DirEntry* loadRoot();

// Create DirEntry (assigns a free block)
DirEntry* createDirEntry(char* name, char type, DirEntry* parent);

// Load direntry from blockAddress
DirEntry* loadDirEntry(unsigned short blockAddress);

// Saves DirEntry to block address (own address)
void saveDirEntry(DirEntry* dirent);

#endif