#include "t2fs.h"
#include "EOperationStatus.h"
#include "utils.h"
#include "TBool.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
Fun��o:	Criar um novo diret�rio.
	O caminho desse novo diret�rio � aquele informado pelo par�metro "pathname".
		O caminho pode ser ser absoluto ou relativo.
	S�o considerados erros de cria��o quaisquer situa��es em que o diret�rio n�o possa ser criado.
		Isso inclui a exist�ncia de um arquivo ou diret�rio com o mesmo "pathname".

Entra:	pathname -> caminho do diret�rio a ser criado

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
	Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int mkdir2(char *pathname)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Return value
	EOperationStatus result = EOpUnknownError;

	// If pathname does not exists
	if ((pathname != NULL) && (exists(pathname) == NULL))
	{
		// Path delimiter
		char delimiter[2] = "/";

		// Intermediate string to avoid modifying the input
		char* intString = calloc(strlen(pathname) + 1, sizeof(char));

		strcpy(intString, pathname);

		// Tokenize
		char* token = strtok(intString, delimiter);
		char* lastToken = calloc(32, sizeof(char));
		char* pathToParent = calloc(1, strlen(pathname+1));
		
		// Process the first char
		// If from current dir
		if ((strlen(token) == 1) && (strncmp(token, ".", 1) == 0))
		{
			// Process from current path
		}
		// else if from parent dir
		else if ((strlen(token) == 2) && (strncmp(token, "..", 2) == 0))
		{
			// Process from current path parent
			// Must be a valid address
			if (gp_currentDirEntry->m_parentAddress != 0)
			{
				strncat(pathToParent, intString, 2);
				strcat(pathToParent, delimiter);
			}
		}
		// Absolute path
		else
		{
			strcat(pathToParent, delimiter);
		}
		
		// Signals the end of the search
		TBool endOfSearch = false;

		// Non empty string
		while (!endOfSearch)
		{
			strcpy(lastToken, token);
			token = strtok(NULL, delimiter);
			endOfSearch = (token == NULL);
			if (token != NULL)
			{
				strcat(pathToParent, lastToken);
				strcat(pathToParent, delimiter);
			}
		}

		DirEntry* parent = exists(pathToParent);
		if (parent != NULL)
		{
			if (addToIBlock(parent, createDirEntry(lastToken, 0x02, parent)))
			{
				result = EOpSuccess;
			}
		}

		free(intString);
		free(lastToken);
		free(pathToParent);
	}

	return result;
}
