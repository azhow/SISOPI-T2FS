#include <stdlib.h>
#include "TestReaddir2.h"
#include "t2fs.h"

ETestStatus testReaddir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "/a";
	DIRENT2 *dirRead = calloc(1, sizeof(DIRENT2));

	if (readdir2(opendir2(testPath), dirRead) != -1)
	{
		testResult = TestSuccess;
	}

	free(dirRead);

	return testResult;
}