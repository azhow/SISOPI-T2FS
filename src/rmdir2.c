#include "t2fs.h"
#include "EOperationStatus.h"
#include "direntry.h"
#include "bitmap.h"
#include "utils.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
Fun��o:	Apagar um subdiret�rio do disco.
	O caminho do diret�rio a ser apagado � aquele informado pelo par�metro "pathname".
	S�o considerados erros quaisquer situa��es que impe�am a opera��o.
		Isso inclui:
			(a) o diret�rio a ser removido n�o est� vazio;
			(b) "pathname" n�o existente;
			(c) algum dos componentes do "pathname" n�o existe (caminho inv�lido);
			(d) o "pathname" indicado n�o � um arquivo;

Entra:	pathname -> caminho do diret�rio a ser criado

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
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