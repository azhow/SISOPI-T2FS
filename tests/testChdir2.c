#include "testMain.h"
#include "EOperationStatus.h"
#include "t2fs.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>

ETestStatus testChdir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char path[] = "/c/";
	// To test against cwd 
	char* pathTest = calloc(10, sizeof(char));
	
	if ((chdir2(path) == EOpSuccess) && (getcwd2(pathTest, 10) == EOpSuccess) && (strcmp(pathTest, path) == EOpSuccess))
	{
		testResult = TestSuccess;
	}

	return testResult;
}