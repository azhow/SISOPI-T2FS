#include "testMain.h"
#include "t2fs.h"

ETestStatus testOpendir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "./arroz";
	if (opendir2(testPath) != -1)
	{
		testResult = TestSuccess;
	}
	// This one does not exists
	char testPath2[] = "/feijao";
	if ((opendir2(testPath2) == -1) && (testResult != TestError))
	{
		testResult = TestSuccess;
	}
	else
	{
		testResult = TestError;
	}

	return testResult;
}