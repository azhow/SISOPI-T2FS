#include "testMain.h"
#include "t2fs.h"

ETestStatus testCreate2()
{
	// Test result
	ETestStatus testResult = TestError;

	char *fileName = "arquivo";
	if (create2(fileName) != -1)
	{
		testResult = TestSuccess;
	}

	return testResult;
}