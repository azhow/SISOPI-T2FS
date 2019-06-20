#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "openfiletable.h"
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
	
/*-----------------------------------------------------------------------------
Fun��o:	Apagar um arquivo do disco.
	O nome do arquivo a ser apagado � aquele informado pelo par�metro "filename".

Entra:	filename -> nome do arquivo a ser apagado.

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int delete2 (char *filename)
{
    EOperationStatus result = EOpUnknownError;

    // Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}
    // Search in current directory for file to delete
    char* pathname = "./";
	strcat(pathname, filename);

	// DirEntry of the file we are searching for
	DirEntry* searchEntry = exists(pathname);

	// File exists
	if (searchEntry != NULL)
	{   
        // Is not a directory
        if (searchEntry->m_filetype == 0x01)
        {
            int handle = 0;
            for (handle = 0; handle < 10; handle++){
                DirEntry* dirEntry = gp_openFileTable->m_openFiles[handle]->m_openFileDirEntry;
                // File is open
                if ((strcmp(dirEntry->m_name, filename) == 0) && dirEntry->m_ownAddress == searchEntry->m_ownAddress)
                {
                    close2(handle);
                }
            }
            // Free file blocks
            unsigned int size = searchEntry->m_iBlock->m_size;
            int i;
            for (i = 0; i < size; i++)
            {
                freeBlock(searchEntry->m_iBlock->m_contents[i]);
            }
            searchEntry->m_iBlock->m_size =0;

            result = EOpSuccess;
        }
	}
	
	return result;
}