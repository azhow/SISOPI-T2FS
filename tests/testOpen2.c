#include "testMain.h"
#include "t2fs.h"

ETestStatus testOpen2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "/a";
	if (open2(testPath) != -1)
	{
		testResult = TestSuccess;
	}

	return testResult;
}