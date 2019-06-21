#include "testMain.h"
#include "t2fs.h"
#include "EOperationStatus.h"

ETestStatus testFormat2()
{
	// Test result
	ETestStatus testResult = TestError;

	// This call should return error
	if (format2(0) == EOpUnknownError)
	{
		testResult = TestSuccess;
	}

	// This call should be successful
	if ((format2(1) == EOpSuccess) && (testResult == TestSuccess))
	{
		testResult = TestSuccess;
	}

	return testResult;
}