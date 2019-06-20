#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Fecha o arquivo identificado pelo par�metro "handle".

Entra:	handle -> identificador do arquivo a ser fechado

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int close2 (FILE2 handle)
{
	EOperationStatus result = EOpUnknownError;
    
    // Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// If handle is valid
	if ((handle > -1) && (handle < 10))
	{
		removeOpenFileFromTable((unsigned int)handle);
		result = EOpSuccess;
	}

	return result;
}
