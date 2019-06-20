#include <stdio.h>
#include "testMain.h"
#include "t2fs.h"
#include "ETestStatus.h"

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

	// mkdir2 test
	// Currently running test 
	printf("mkdir2_test:\t");
	// Run the test
	currentTestStatus = testMkdir2();
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

	// readdir2 test
	// Currently running test 
	printf("readdir2_test:\t");
	// Run the test
	currentTestStatus = testReaddir2();
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

	// closedir2 test
	// Currently running test 
	printf("closedir2_test:\t");
	// Run the test
	currentTestStatus = testClosedir2();
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

	// chdir2 test
	// Currently running test 
	printf("chdir2_test:\t");
	// Run the test
	currentTestStatus = testChdir2();
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

	// getcwd2 test
	// Currently running test 
	printf("getcwd2_test:\t");
	// Run the test
	currentTestStatus = testGetcwd2();
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
	
	// Open2 test
	// Currently running test 
	printf("open2_test:\t");
	// Run the test
	currentTestStatus = testOpen2();
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

	// bitmap test
	// Currently running test 
	printf("bitmap_test:\t");
	// Run the test
	currentTestStatus = testBitmap();
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

	// create2 test
	// Currently running test 
	printf("create2_test:\t");
	// Run the test
	currentTestStatus = testCreate2();
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