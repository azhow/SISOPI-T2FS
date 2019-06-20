#include "testMain.h"
#include "t2fs.h"
#include "ETestStatus.h"
#include "EOperationStatus.h"
#include <string.h>
#include <stdlib.h>

// getcwd2 function test
ETestStatus testGetcwd2()
{
	// Test result
	ETestStatus testResult = TestError;

	char path[] = "/c/";
	// To test against cwd 
	char* pathTest = calloc(10, sizeof(char));

	if ((chdir2(path) == EOpSuccess) && (getcwd2(pathTest, 10) == EOpSuccess) && (strcmp(pathTest, path) == EOpSuccess))
	{
		char newPath[] = "/";
		strcpy(pathTest, "/");
		if ((chdir2(newPath) == EOpSuccess) && (getcwd2(pathTest, 10) == EOpSuccess) && (strcmp(pathTest, newPath) == EOpSuccess))
		{
			testResult = TestSuccess;
		}
	}

	return testResult;
}