#include "t2fs.h"
#include "utils.h"

/*-----------------------------------------------------------------------------
Função:	Abre um diretório existente no disco.
	O caminho desse diretório é aquele informado pelo parâmetro "pathname".
	Se a operação foi realizada com sucesso, a função:
		(a) deve retornar o identificador (handle) do diretório
		(b) deve posicionar o ponteiro de entradas (current entry) na primeira posição válida do diretório "pathname".
	O handle retornado será usado em chamadas posteriores do sistema de arquivo para fins de manipulação do diretório.

Entra:	pathname -> caminho do diretório a ser aberto

Saída:	Se a operação foi realizada com sucesso, a função retorna o identificador do diretório (handle).
	Em caso de erro, será retornado um valor negativo.
-----------------------------------------------------------------------------*/
DIR2 opendir2(char *pathname)
{
	// Returned handle
	DIR2 returnHandle = -1;

	// Should transverse the directories to find the given path
	// if found, then assign the handle and do the other related operations
	// like finding a new unassigned handle

	// Return
	return returnHandle;
}