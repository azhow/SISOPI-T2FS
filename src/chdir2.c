#include "t2fs.h"
#include "utils.h"
#include "EOperationStatus.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Função:	Altera o diretório atual de trabalho (working directory).
		O caminho desse diretório é informado no parâmetro "pathname".
		São considerados erros:
			(a) qualquer situação que impeça a realização da operação
			(b) não existência do "pathname" informado.

Entra:	pathname -> caminho do novo diretório de trabalho.

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
		Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int chdir2(char *pathname)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Operation result
	EOperationStatus opStatus = EOpUnknownError;
	// Searches for the pathname
	DirEntry* newDir = exists(pathname);
	// If dir was found
	if (newDir != NULL)
	{
		// Free the current dir entry
		free(gp_currentDirEntry);
		// Point to the new one
		gp_currentDirEntry = newDir;
		// Update operation status
		opStatus = EOpSuccess;
	}

	return opStatus;
}