#include <string.h>
#include "utils.h"
#include "direntry.h"

// Definition of the current path (should initialize it rather)
// Current working path
char g_currentPath[32];

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

	DirEntry dirEnt;
	dirEnt.m_filetype = 0x01;
	printf("DirEntry size: %d\n", sizeof(dirEnt));
	printf("m_name: %d\n", sizeof(dirEnt.m_name));
	printf("m_filetype: %d\n", sizeof(dirEnt.m_filetype));
	printf("m_size: %d\n", sizeof(dirEnt.m_size));
	printf("m_iBlockAddress: %d\n", sizeof(dirEnt.m_iBlockAddress));
	printf("m_entries: %d\n", sizeof(dirEnt.m_entries));

	return result;
}