#include <stdlib.h>
#include "testMain.h"
#include "t2fs.h"
#include "openfiletable.h"

ETestStatus testClosedir2()
{
	// Test result
	ETestStatus testResult = TestError;

	char testPath[] = "/c";

	// Opens dir
	DIR2 handle = opendir2(testPath);
	if (handle != -1)
	{
		// If entry is valid and exists
		if (gp_openFileTable->m_openFiles[handle] != NULL)
		{
			// Close dir
			closedir2(handle);
			// Check if the entry is still valid (should not be)
			if (gp_openFileTable->m_openFiles[handle] == NULL)
			{
				testResult = TestSuccess;
			}
		}
	}

	return testResult;
}