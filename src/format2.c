#include <stdlib.h>
#include <string.h>
#include "t2fs.h"
#include "utils.h"
#include "superblock.h"
#include "apidisk.h"
#include "bitmap.h"

#include <stdio.h>

/*-----------------------------------------------------------------------------
Fun��o:	Formata um disco virtual

Entra:	sectors_per_block -> tamanho de um bloco de dados em setores

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int format2(int sectors_per_block)
{
	// Operation status
	EOperationStatus retValue = EOpUnknownError;

	// The FS only makes sense when sectors per block is bigger than 0
	if (sectors_per_block > 0)
	{
		// Initialize superblock (save to disk also)
		initializeSuperblock(sectors_per_block);
		// Initialize bitmap
		gp_memBitmap = malloc(sizeof(Bitmap));
		// Initialize all memory free
		memset(gp_memBitmap->m_map, 0x31, sizeof(gp_memBitmap->m_map));
		// Create root dir and saves to disk
		gp_currentDirEntry = createDirEntry("root", 0x02, NULL);
		// Initializes library
		initialize();
		retValue = EOpSuccess;
	}


	return retValue;
}