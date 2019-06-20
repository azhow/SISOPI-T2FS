#include "testMain.h"
#include "bitmap.h"
#include "EOperationStatus.h"
#include <stdlib.h>
#include <string.h>

#include "superblock.h"

ETestStatus testBitmap()
{
	ETestStatus testResult = TestError;

	loadBitmap();

	// Bitmap should be filled with "1"
	memset(gp_memBitmap->m_map, 0x31, sizeof(gp_memBitmap->m_map));

	saveBitmap();

	gp_superblock = calloc(1, sizeof(Superblock));
	// For this test only
	gp_superblock->m_bitmapSize = 4000;
	allocBlock();
	allocBlock();
	allocBlock();
	allocBlock();
	allocBlock();
	allocBlock();
	freeBlock(2);
	freeBlock(4);
	allocBlock();

	return testResult;
}