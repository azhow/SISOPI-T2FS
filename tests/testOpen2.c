#include "TestOpen2.h"

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