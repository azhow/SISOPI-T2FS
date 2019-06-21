#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include "bitmap.h"
#include "superblock.h"
#include <stdlib.h>
#include <string.h>
#include "EOperationStatus.h"

/*-----------------------------------------------------------------------------
Fun��o:	Realiza a escrita de "size" bytes no arquivo identificado por "handle".
	Os bytes a serem escritos est�o na �rea apontada por "buffer".
	Ap�s a escrita, o contador de posi��o (current pointer) deve ser ajustado para o byte seguinte ao �ltimo escrito.

Entra:	handle -> identificador do arquivo a ser escrito
	buffer -> buffer de onde pegar os bytes a serem escritos no arquivo
	size -> n�mero de bytes a serem escritos

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna o n�mero de bytes efetivamente escritos.
	Em caso de erro, ser� retornado um valor negativo.
-----------------------------------------------------------------------------*/
int write2 (FILE2 handle, char *buffer, int size)
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

        // Write while there is space and alloc space as necessary
        // TBool needAnotherBlock = (sizeof(unsigned short) * buffer) > (gp_superblock->m_sectorsPerBlock * SECTOR_SIZE);
        
        // int blocks = file->m_iBlock->m_size;

        // memcpy(buffer, file->m_iBlock->m_contents, size);
        // strncat(dest,src, size);
        // result = strlen();

        // Set current pointer to next byte
        // seek(handle, next_byte);
    }

    return result;
}