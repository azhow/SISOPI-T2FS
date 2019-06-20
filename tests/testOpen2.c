#include "testMain.h"
#include "t2fs.h"
#include <string.h>

ETestStatus testOpen2()
{
	// Test result
	ETestStatus testResult = TestError;

	// Create file
	char filename[] = "arquivo";
	FILE2 handle = create2(filename);

	char path[] = "./";
	strcat(path, filename);

	// Close file
	close2(handle);
	
	// Open file
	if (open2(path) != -1)
	{
		testResult = TestSuccess;
	}

	return testResult;
}