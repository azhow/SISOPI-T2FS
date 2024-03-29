#include "t2fs.h"
#include "utils.h"
#include "TBool.h"
#include "EOperationStatus.h"
#include "apidisk.h"
#include "apidisk.h"
#include "superblock.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printReverse(char str[], char* out)
{
	int length = strlen(str);

	// Traverse string from end 
	int i, offset = 0;
	for (i = length - 1; i >= 0; i--) {
		if (str[i] == '/') {

			// putting the NULL character at the  
			// position of space characters for 
			// next iteration.          
			str[i] = '\0';

			// Start from next charatcer      
			sprintf(out + offset, "%s/", &(str[i]) + 1);
			offset = offset + strlen(&(str[i]) + 1) + 1;
		}
	}

	// printing the last word 
	sprintf(out + offset, "%s", str);
}

/*-----------------------------------------------------------------------------
Fun��o:	Informa o diret�rio atual de trabalho.
		O "pathname" do diret�rio de trabalho deve ser copiado para o buffer indicado por "pathname".
			Essa c�pia n�o pode exceder o tamanho do buffer, informado pelo par�metro "size".
		S�o considerados erros:
			(a) quaisquer situa��es que impe�am a realiza��o da opera��o
			(b) espa�o insuficiente no buffer "pathname", cujo tamanho est� informado por "size".

Entra:	pathname -> buffer para onde copiar o pathname do diret�rio de trabalho
		size -> tamanho do buffer pathname

Sa�da:	Se a opera��o foi realizada com sucesso, a fun��o retorna "0" (zero).
		Em caso de erro, ser� retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int getcwd2(char *pathname, int size)
{
	// Not initialized library yet
	if (gp_currentDirEntry == NULL)
	{
		initialize();
	}

	// Operation result
	EOperationStatus opStatus = EOpUnknownError;
	// Initial directory
	DirEntry* initialDir = gp_currentDirEntry;
	// Intermediary string
	char* path = calloc(size, sizeof(char));
	// Signal if string is already full
	TBool noSpaceLeft = false;

	// Note that the string is built reverted
	// While there are more directories and have not exploded the string size
	while ((initialDir->m_ownAddress != 0x0) && (!noSpaceLeft))
	{
		// If there's space in the string
		if ((strlen(initialDir->m_name) + strlen(path) + 2) < size)
		{
			// Append separator to path
			strcat(path, "/");
			// Append to path
			strcat(path, initialDir->m_name);
		}
		else
		{
			// No space left for the string
			noSpaceLeft = true;
		}
		// Update dir
		initialDir = loadDirEntry(initialDir->m_parentAddress);
	}

	// If added all to string, the op was successfull
	if (!noSpaceLeft)
	{
		// Append separator to the end of path
		strcat(path, "/");

		printReverse(path, pathname);
		// Update result
		opStatus = EOpSuccess;
	}

	// Free allocated memory
	free(path);

	return opStatus;
}