#include "t2fs.h"
#include "utils.h"
#include "EOperationStatus.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Altera o diret�rio atual de trabalho (working directory).
		O caminho desse diret�rio � informado no par�metro "pathname".
		S�o considerados erros:
			(a) qualquer situa��o que impe�a a realiza��o da opera��o
			(b) n�o exist�ncia do "pathname" informado.

Entra:	pathname -> caminho do novo diret�rio de trabalho.

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
		Em caso de erro, ser� retornado um valor diferente de zero.
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