#include "t2fs.h"
#include "openfiletable.h"
#include "EOperationStatus.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Reposiciona o contador de posi��es (current pointer) do arquivo identificado por "handle".
	A nova posi��o � determinada pelo par�metro "offset".
	O par�metro "offset" corresponde ao deslocamento, em bytes, contados a partir do in�cio do arquivo.
	Se o valor de "offset" for "-1", o current_pointer dever� ser posicionado no byte seguinte ao final do arquivo,
		Isso � �til para permitir que novos dados sejam adicionados no final de um arquivo j� existente.

Entra:	handle -> identificador do arquivo a ser escrito
	offset -> deslocamento, em bytes, onde posicionar o "current pointer".

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int seek2(FILE2 handle, DWORD offset)
{
	EOperationStatus result = EOpUnknownError;

	if ((handle > 0) && (handle < 10))
	{
		if (offset >= 0)
		{
			if (gp_openFileTable->m_openFiles + handle != NULL)
			{
				gp_openFileTable->m_openFiles[handle]->m_filepointer = offset;
			}
		}
		else
		{
			if (gp_openFileTable->m_openFiles + handle != NULL)
			{
				gp_openFileTable->m_openFiles[handle]->m_filepointer = gp_openFileTable->m_openFiles[handle]->m_openFileDirEntry->m_size + 1;
			}
		}
		result = EOpSuccess;
	}

	return result;
}
