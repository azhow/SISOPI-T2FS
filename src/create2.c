#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include "bitmap.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
Fun��o: Criar um novo arquivo.
	O nome desse novo arquivo � aquele informado pelo par�metro "filename".
	O contador de posi��o do arquivo (current pointer) deve ser colocado na posi��o zero.
	Caso j� exista um arquivo ou diret�rio com o mesmo nome, o mesmo  terá  seu  conteúdo  removido e 
    assumirá um tamanho de zero bytes.
	A fun��o deve retornar o identificador (handle) do arquivo.
	Esse handle ser� usado em chamadas posteriores do sistema de arquivo para fins de manipula��o do arquivo criado.

Entra:	filename -> nome do arquivo a ser criado.

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o handle do arquivo (n�mero positivo).
	Em caso de erro, deve ser retornado um valor negativo.
-----------------------------------------------------------------------------*/
FILE2 create2 (char *filename)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Returned handle
	FILE2 returnHandle = -1;

    char path[] = "./";
	strcat(path, filename);

	// DirEntry of the entry we are searching for
	DirEntry* file = exists(path);

	// File exists
	if (file != NULL)
	{
        // Erase content
	    unsigned int size = file->m_iBlock->m_size;
		int i;
		for (i = 0; i < size; i++)
		{
			freeBlock(file->m_iBlock->m_contents[i]);
		}
		file->m_size = 0;
		file->m_iBlock->m_size =0;
	}
	// File does not exist
    else
    {
        // Create file
		file = createDirEntry(filename, 0x01, gp_currentDirEntry);
    }

    returnHandle = addOpenFileToTable(file);

	// Return
	return returnHandle;
}