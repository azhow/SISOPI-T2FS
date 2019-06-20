#include "testMain.h"
#include "t2fs.h"
#include "openfiletable.h"
#include <stdlib.h>

ETestStatus testDelete2()
{
	// Test result
	ETestStatus testResult = TestError;
	// Create file
	char filename[] = "arquivo";
	FILE2 handle = create2(filename);

    // If entry is valid and exists
    if (gp_openFileTable->m_openFiles[handle] != NULL)
    {
        // Delete file
        if (delete2(filename) == 0)
        {
            // Check if the entry is still valid (should not be)
            if (gp_openFileTable->m_openFiles[handle] == NULL)
            {
                testResult = TestSuccess;
            }
        }
    }

	return testResult;
}