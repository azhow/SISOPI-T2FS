#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Fecha o diret�rio identificado pelo par�metro "handle".

Entra:	handle -> identificador do diret�rio que se deseja fechar (encerrar a opera��o).

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
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