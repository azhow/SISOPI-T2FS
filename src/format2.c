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
		// Initialize superblock (save to disk also)
		initializeSuperblock(sectors_per_block);
		// Create root dir and saves to disk
		gp_currentDirEntry = createDirEntry("root", 0x02, NULL);
	}

	// Initializes library
	initialize();

	return retValue;
}