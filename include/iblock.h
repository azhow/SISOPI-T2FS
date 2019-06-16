#ifndef __iblock_h__
#define __iblock_h__

// Pragma directive to tell the compiler to not add any padding, so the struct has a predictable size 256
#pragma pack(push, 1)

// Directory entry
typedef struct
{
	unsigned short m_contents[128]; // Addresses contained in the contents
} iBlock;

#pragma pack(pop)

// Serializes an iBlock to write to disk
// The buffer should have size == 256
void serialize_iBlock(iBlock* s_iblock, unsigned char* buffer);

// Deserializes an iBlock read from disk
// The buffer should have size == 256
iBlock* deserialize_iBlock(unsigned char* buffer);

#endif