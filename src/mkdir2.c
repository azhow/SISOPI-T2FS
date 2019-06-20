#include "t2fs.h"
#include "EOperationStatus.h"
#include "utils.h"
#include "TBool.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
Função:	Criar um novo diretório.
	O caminho desse novo diretório é aquele informado pelo parâmetro "pathname".
		O caminho pode ser ser absoluto ou relativo.
	São considerados erros de criação quaisquer situações em que o diretório não possa ser criado.
		Isso inclui a existência de um arquivo ou diretório com o mesmo "pathname".

Entra:	pathname -> caminho do diretório a ser criado

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
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
