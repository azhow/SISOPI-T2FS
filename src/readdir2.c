#include <string.h>
#include "t2fs.h"
#include "utils.h"
#include "EOperationStatus.h"
#include "openfiletable.h"

/*-----------------------------------------------------------------------------
Fun��o:	Realiza a leitura das entradas do diret�rio identificado por "handle".
	A cada chamada da fun��o � lida a entrada seguinte do diret�rio representado pelo identificador "handle".
	Algumas das informa��es dessas entradas devem ser colocadas no par�metro "dentry".
	Ap�s realizada a leitura de uma entrada, o ponteiro de entradas (current entry) deve ser ajustado para a pr�xima entrada v�lida, seguinte � �ltima lida.
	S�o considerados erros:
		(a) qualquer situa��o que impe�a a realiza��o da opera��o
		(b) t�rmino das entradas v�lidas do diret�rio identificado por "handle".

Entra:	handle -> identificador do diret�rio cujas entradas deseja-se ler.
	dentry -> estrutura de dados onde a fun��o coloca as informa��es da entrada lida.

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero ( e "dentry" n�o ser� v�lido)
-----------------------------------------------------------------------------*/
int readdir2(DIR2 handle, DIRENT2 *dentry)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Status of the operation
	EOperationStatus operationStatus = EOpUnknownError;
	
	// Check if the handle is valid
	if ((handle >= 0) && (handle < 9))
	{
		// Get the handle content and assign it to the entry reference
		// Fills the dentry
		strcpy(dentry->name, ((DirEntry*)((OpenFile*)gp_openFileTable->m_openFiles[handle])->m_openFileDirEntry)->m_name);
		dentry->fileType = ((DirEntry*)((OpenFile*)gp_openFileTable->m_openFiles[handle])->m_openFileDirEntry)->m_filetype;
		dentry->fileSize = ((DirEntry*)((OpenFile*)gp_openFileTable->m_openFiles[handle])->m_openFileDirEntry)->m_size;
		operationStatus = EOpSuccess;
	}

	// Return
	return operationStatus;
}