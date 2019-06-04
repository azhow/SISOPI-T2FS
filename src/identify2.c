#include <string.h>
#include "EOperationStatus.h"
#include "t2fs.h"

/*-----------------------------------------------------------------------------
Função:	Informa a identificação dos desenvolvedores do T2FS.
-----------------------------------------------------------------------------*/
int identify2 (char *name, int size) {
	// Operation status to be returned
	EOperationStatus returnCode = OpUknownError;

    strncpy (name, "Arthur Zachow - 00277951\nEmily Calvet - 00242277", size);
    
	returnCode = OpSuccess;

	return returnCode;
}