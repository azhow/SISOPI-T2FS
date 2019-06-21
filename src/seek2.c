#include "t2fs.h"
#include "openfiletable.h"
#include "EOperationStatus.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Função:	Reposiciona o contador de posições (current pointer) do arquivo identificado por "handle".
	A nova posição é determinada pelo parâmetro "offset".
	O parâmetro "offset" corresponde ao deslocamento, em bytes, contados a partir do início do arquivo.
	Se o valor de "offset" for "-1", o current_pointer deverá ser posicionado no byte seguinte ao final do arquivo,
		Isso é útil para permitir que novos dados sejam adicionados no final de um arquivo já existente.

Entra:	handle -> identificador do arquivo a ser escrito
	offset -> deslocamento, em bytes, onde posicionar o "current pointer".

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
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
