#include "testMain.h"
#include "ETestStatus.h"
#include "bitmap.h"
#include <stdio.h>
#include <string.h>

ETestStatus testBitmap()
{
    char bitmapInitialized[4000];
    int i;
    for (i = 0; i < 4000; i++) {
        bitmapInitialized[i] = '1';
    }

	bitmap* bitinit = bitmap_init(4000);
	printf("sizeof char - %d", sizeof(char));
	printf("\nmap- %s",&bitinit->map[0]);

    if (strcmp(bitinit->map,bitmapInitialized) != 0) {
		perror("Bitmap not initialized correctly");
        return TestError;
    }
    
	printf("\nsize- %d",bitinit->size);

	printf("\nbit 3- %d", bitinit->get(bitinit, 3));
	 bitinit->set(bitinit, 3);
	// bitinit->map[3] = '0';
	printf("\nbit 3 set- %d", bitinit->get(bitinit, 3));
	 bitinit->reset(bitinit, 3);
	// bitinit->map[3] = '1';
	printf("\nbit 3 reset- %d\n", bitinit->get(bitinit, 3));

	bitmap_free(bitinit);

	return TestSuccess;
}