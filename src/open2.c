#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Abre um arquivo existente no disco.
	O nome desse novo arquivo � aquele informado pelo par�metro "filename".
	Ao abrir um arquivo, o contador de posi��o do arquivo (current pointer) deve ser colocado na posi��o zero.
	A fun��o deve retornar o identificador (handle) do arquivo.
	Esse handle ser� usado em chamadas posteriores do sistema de arquivo para fins de manipula��o do arquivo criado.
	Todos os arquivos abertos por esta chamada s�o abertos em leitura e em escrita.
	O ponto em que a leitura, ou escrita, ser� realizada � fornecido pelo valor current_pointer (ver fun��o seek2).

Entra:	filename -> nome do arquivo a ser apagado.

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o handle do arquivo (n�mero positivo)
	Em caso de erro, deve ser retornado um valor negativo
-----------------------------------------------------------------------------*/
FILE2 open2(char *pathname)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Returned handle
	FILE2 returnHandle = -1;

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