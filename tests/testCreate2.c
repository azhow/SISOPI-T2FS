#include "testMain.h"
#include "t2fs.h"
#include "openfiletable.h"
#include <stdlib.h>

ETestStatus testCreate2()
{
	// Test result
	ETestStatus testResult = TestError;

	// Create file
	char filename[] = "arquivo";
	FILE2 handle = create2(filename);

	// Handle is valid
	if (handle != -1)
	{
		// If entry is valid and exists
		if (gp_openFileTable->m_openFiles[handle] != NULL)
		{
			testResult = TestSuccess;
		}
	}
	return testResult;
}