#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Abre um diret�rio existente no disco.
	O caminho desse diret�rio � aquele informado pelo par�metro "pathname".
	Se a opera��o foi realizada com sucesso, a fun��o:
		(a) deve retornar o identificador (handle) do diret�rio
		(b) deve posicionar o ponteiro de entradas (current entry) na primeira posi��o v�lida do diret�rio "pathname".
	O handle retornado ser� usado em chamadas posteriores do sistema de arquivo para fins de manipula��o do diret�rio.

Entra:	pathname -> caminho do diret�rio a ser aberto

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o identificador do diret�rio (handle).
	Em caso de erro, ser� retornado um valor negativo.
-----------------------------------------------------------------------------*/
DIR2 opendir2(char *pathname)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Returned handle
	DIR2 returnHandle = -1;

	// DirEntry of the entry we are searching for
	DirEntry* searchEntry = exists(pathname);

	// Should transverse the directories to find the given path
	if (searchEntry != NULL)
	{
		returnHandle = addOpenFileToTable(searchEntry);
	}

	// Return
	return returnHandle;
}