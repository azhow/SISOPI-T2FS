#include <stdio.h>
#include "testMain.h"
#include "t2fs.h"
#include "ETestStatus.h"
#include "TestFormat2.h"

ETestStatus runAllTests()
{
	// All tests variable
	ETestStatus overallTestStatus = TestSuccess;
	// Current test variable
	ETestStatus currentTestStatus = TestSuccess;

	// example test success
	// Currently running test 
	printf("format2_test:\t");
	// Run the test
	currentTestStatus = testFormat2();
	// Check if test runned successfully
	if (currentTestStatus != TestSuccess)
	{
		overallTestStatus -= TestError;
		printf("FAILED\n");
	}
	else
	{
		printf("SUCCESS\n");
	}

	// If any test failed
	if (overallTestStatus != 0)
	{
		printf("Number of failed tests: %d\n", overallTestStatus);
	}

	return overallTestStatus;
}