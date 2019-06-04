#include "t2fs.h"
#include "utils.h"
#include "apidisk.h"

/*-----------------------------------------------------------------------------
Função:	Formata um disco virtual

Entra:	sectors_per_block -> tamanho de um bloco de dados em setores

Saída:	Se a operação foi realizada com sucesso, a função retorna "0" (zero).
	Em caso de erro, será retornado um valor diferente de zero.
-----------------------------------------------------------------------------*/
int format2(int sectors_per_block)
{
	// TODO fomat disk with our options
	// We have 4000 sectors in the disk
	unsigned char buff[40] = "aaaaaaaaaaaaaaaaaa";
	write_sector(1000, buff);

	return 0;
}