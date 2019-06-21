#include "t2fs.h"
#include "EOperationStatus.h"
#include "direntry.h"
#include "bitmap.h"
#include "utils.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Função:	Apagar um subdiretório do disco.
	O caminho do diretório a ser apagado é aquele informado pelo parâmetro "pathname".
	São considerados erros quaisquer situações que impeçam a operação.
		Isso inclui:
			(a) o diretório a ser removido não está vazio;
			(b) "pathname" não existente;
			(c) algum dos componentes do "pathname" não existe (caminho inválido);
			(d) o "pathname" indicado não é um arquivo;

Entra:	pathname -> caminho do diretório a ser criado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int 
rmdir2(char *pathname)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Return value
	EOperationStatus result = EOpUnknownError;
	// If valid input
	if ((pathname != NULL))
	{
		// Dir
		DirEntry* foundDir = exists(pathname);
		// If pathname exists and is directory
		if ((foundDir != NULL) && (foundDir->m_filetype == 0x02))
		{
			// Verifies if directory is empty
			if (emptyDir(foundDir))
			{
				// If empty delete it (free block of memory)
				freeBlock(foundDir->m_ownAddress);

				unsigned short addToRemove = foundDir->m_ownAddress;
				// Updates parent entry
				foundDir = loadDirEntry(foundDir->m_parentAddress);

				// Remove from directory (iblock)
				removeFromDir(foundDir, addToRemove);

				result = EOpSuccess;
			}
			free(foundDir);
		}
	}

	return result;
}