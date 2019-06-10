#include <string.h>
#include "utils.h"

// Definition of the current path (should initialize it rather)
// Current working path
char g_currentPath[MAX_FILE_NAME_SIZE + 1];

#include <stdio.h>

// Checks the existence of a given path
TBool exists(char *pathname)
{
	// Return of the operation
	TBool result = false;
	// Path delimiter
	char delimiter[2] = "/";

	// Tokenize
	char* token = strtok(pathname, delimiter);

	// Non empty string
	if (token != NULL)
	{
		// Process the first char
		// If from current dir
		if ((strlen(token) == 1) && (strncmp(token, ".", 1) == 0))
		{
			// Process from current path
			printf("Current path\n");
		}
		// else if from parent dir
		else if ((strlen(token) == 2) && (strncmp(token, "..", 2) == 0))
		{
			// Process from current path parent
			printf("Current path parent\n");
		}
		// Absolute path
		else
		{
			// Process from root
			printf("Absolute path\n");
		}

		// Does the current dir exists?
		TBool currDirExists = true;
		// Transverse
		while ((token != NULL) && currDirExists)
		{
			token = strtok(NULL, delimiter);
		}
	}
	// Might be root directory?
	else
	{
		// 
	}

	return result;
}