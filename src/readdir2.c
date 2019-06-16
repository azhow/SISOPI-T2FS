#include <string.h>
#include "t2fs.h"
#include "utils.h"
#include "EOperationStatus.h"
#include "openfiletable.h"

/*-----------------------------------------------------------------------------
Função:	Realiza a leitura das entradas do diretório identificado por "handle".
	A cada chamada da função é lida a entrada seguinte do diretório representado pelo identificador "handle".
	Algumas das informações dessas entradas devem ser colocadas no parâmetro "dentry".
	Após realizada a leitura de uma entrada, o ponteiro de entradas (current entry) deve ser ajustado para a próxima entrada válida, seguinte à última lida.
	São considerados erros:
		(a) qualquer situação que impeça a realização da operação
		(b) término das entradas válidas do diretório identificado por "handle".

Entra:	handle -> identificador do diretório cujas entradas deseja-se ler.
	dentry -> estrutura de dados onde a função coloca as informações da entrada lida.

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero ( e "dentry" não será válido)
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