#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "t2fs.h"
#include "utils.h"
#include "direntry.h"
#include "EOperationStatus.h"
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
	DirEntry* dirEntry = calloc(1, sizeof(DirEntry));
	strcat(dirEntry->m_name, "banana batata");
	dirEntry->m_filetype = 0x01;
	dirEntry->m_size = 0;
	dirEntry->m_iBlockAddress = 200;
	dirEntry->m_parentAddress = 100;
	dirEntry->m_ownAddress = 150;
	dirEntry->m_empty = 56;

	unsigned char buff[256] = { 0 };
	serialize_DirEntry(dirEntry, buff);
	write_sector(100, buff);

	unsigned char buff2[256] = { 0 };
	read_sector(100, buff2);
	DirEntry* readDir = deserialize_DirEntry(buff2);
	printf("%s\n", readDir->m_name);
	printf("%d\n", readDir->m_filetype);
	printf("%d\n", readDir->m_size);
	printf("%d\n", readDir->m_iBlockAddress);
	printf("%d\n", readDir->m_parentAddress);
	printf("%d\n", readDir->m_ownAddress);
	printf("%d\n", readDir->m_empty);


	return 0;
}