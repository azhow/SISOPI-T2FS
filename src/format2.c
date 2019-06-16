#include <stdlib.h>
#include <string.h>
#include "t2fs.h"
#include "utils.h"
#include "superblock.h"
#include "apidisk.h"

#include <stdio.h>

/*-----------------------------------------------------------------------------
Função:	Formata um disco virtual

Entra:	sectors_per_block -> tamanho de um bloco de dados em setores

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int format2(int sectors_per_block)
{
	// Operation status
	EOperationStatus retValue = EOpUnknownError;

	// The FS only makes sense when sectors per block is bigger than 0
	if (sectors_per_block > 0)
	{
		// Superblock struct
		Superblock* psSuperblock = malloc(sizeof(Superblock));
		psSuperblock->m_sectorsPerBlock = sectors_per_block;
		psSuperblock->m_rootAddress = 1;

		// Buffer for the superblock
		unsigned char* pBuffer = calloc(SECTOR_SIZE, sizeof(char));

		// Read sector MBR_SECTOR
		// MUST preserve the old contents
		if (read_sector(MBR_SECTOR, pBuffer) == EOpSuccess)
		{
			// Serializes the superblock
			serialize_Superblock(psSuperblock, pBuffer);
			// Write sector
			retValue = write_sector(MBR_SECTOR, pBuffer);
		}

		// Create root dir
		DirEntry* pRoot = malloc(sizeof(DirEntry));
		// Set the root attributes
		strcpy(pRoot->m_name, "root");
		pRoot->m_filetype = 0x02;
		pRoot->m_ownAddress = 1;
		pRoot->m_iBlockAddress = 2;
		pRoot->m_parentAddress = 0;
		pRoot->m_size = 0;
		memset(pRoot->m_entries, 0, sizeof(pRoot->m_entries));
		pRoot->m_empty = 0;

		// Clears buffer
		memset(pBuffer, 0, sizeof(SECTOR_SIZE));
		serialize_DirEntry(pRoot, pBuffer);
		// Write root directory to disk
		write_sector(pRoot->m_ownAddress, pBuffer);

		// Free buffer
		free(pBuffer);
		free(pRoot);
	}

	// Initializes library
	initialize();

	return retValue;
}