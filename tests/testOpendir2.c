#include "TestOpendir2.h"

ETestStatus testOpendir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "/c";
	if (opendir2(testPath) != -1)
	{
		testResult = TestSuccess;
	}

	return testResult;
}