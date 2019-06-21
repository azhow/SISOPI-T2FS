#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include "bitmap.h"
#include <stdlib.h>
#include <string.h>
#include "EOperationStatus.h"

/*-----------------------------------------------------------------------------
Fun��o:	Realiza a leitura de "size" bytes do arquivo identificado por "handle".
	Os bytes lidos s�o colocados na �rea apontada por "buffer".
	Ap�s a leitura, o contador de posi��o (current pointer) deve ser ajustado para o byte seguinte ao �ltimo lido.

Entra:	handle -> identificador do arquivo a ser lido
	buffer -> buffer onde colocar os bytes lidos do arquivo
	size -> n�mero de bytes a serem lidos

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o n�mero de bytes lidos.
	Se o valor retornado for menor do que "size", ent�o o contador de posi��o atingiu o final do arquivo.
	Em caso de erro, ser� retornado um valor negativo.
-----------------------------------------------------------------------------*/
int read2 (FILE2 handle, char *buffer, int size)
{
    int result = -1;

    // Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

    // Handle is valid
    if ((handle > -1) && (handle < 10))
    {
        // DirEntry* file = gp_openFileTable->m_openFiles[handle]->m_openFileDirEntry;

        // memcpy(buffer, file->m_iBlock->m_contents, size);
        // strncat(dest,src, size);
        // result = strlen(buffer);

        // Set current pointer to next byte
        // seek(handle, next_byte);
    }

    return result;
}
