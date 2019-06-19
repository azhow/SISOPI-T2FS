#include "t2fs.h"
#include "utils.h"
#include "TBool.h"
#include "EOperationStatus.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
Função:	Informa o diretório atual de trabalho.
		O "pathname" do diretório de trabalho deve ser copiado para o buffer indicado por "pathname".
			Essa cópia não pode exceder o tamanho do buffer, informado pelo parâmetro "size".
		São considerados erros:
			(a) quaisquer situações que impeçam a realização da operação
			(b) espaço insuficiente no buffer "pathname", cujo tamanho está informado por "size".

Entra:	pathname -> buffer para onde copiar o pathname do diretório de trabalho
		size -> tamanho do buffer pathname

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
		Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int getcwd2(char *pathname, int size)
{
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
	while ((initialDir->m_parentAddress != 0x0) && (!noSpaceLeft))
	{
		// If there's space in the string
		if ((strlen(initialDir->m_name) + strlen(path) + 1) < size)
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
	}

	// If added all to string, the op was successfull
	if (!noSpaceLeft)
	{
		// Reverses string
		strrev(path);
		// Copy to path
		strcpy(pathname, path);
		// Update result
		opStatus = EOpSuccess;
	}

	// Free allocated memory
	free(path);

	return opStatus;
}