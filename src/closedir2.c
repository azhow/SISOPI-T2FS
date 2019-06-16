#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Função:	Fecha o diretório identificado pelo parâmetro "handle".

Entra:	handle -> identificador do diretório que se deseja fechar (encerrar a operação).

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int 
closedir2(DIR2 handle)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Returned handle
	EOperationStatus result = EOpUnknownError;

	// Should transverse the directories to find the given path
	if ((handle > -1) && (handle < 10))
	{
		removeOpenFileFromTable((unsigned int)handle);
		result = EOpSuccess;
	}

	// Return
	return result;
}