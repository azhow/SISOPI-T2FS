#include <stdlib.h>
#include <string.h>
#include "testMain.h"
#include "t2fs.h"
#include "ETestStatus.h"

ETestStatus testReaddir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "/batata/arroz";
	DIRENT2 *dirRead = calloc(1, sizeof(DIRENT2));

	if (readdir2(opendir2(testPath), dirRead) != -1)
	{
		if ((strcmp(dirRead->name, "arroz") == 0) && (dirRead->fileType == 0x02) && (dirRead->fileSize == 0))
		{
			testResult = TestSuccess;
		}
	}

	free(dirRead);

	return testResult;
}