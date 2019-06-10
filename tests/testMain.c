#include <stdio.h>
#include "testMain.h"
#include "t2fs.h"
#include "ETestStatus.h"
#include "TestFormat2.h"
#include "TestOpendir2.h"

ETestStatus runAllTests()
{
	// All tests variable
	ETestStatus overallTestStatus = TestSuccess;
	// Current test variable
	ETestStatus currentTestStatus = TestSuccess;

	// format2 test
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

	// opendir2 test
	// Currently running test 
	printf("opendir2_test:\t");
	// Run the test
	currentTestStatus = testOpendir2();
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