#include "testMain.h"
#include "ETestStatus.h"
#include "EOperationStatus.h"
#include "t2fs.h"

// rmdir2 function test
ETestStatus testRmdir2()
{
	ETestStatus result = TestError;

	if ((mkdir2("/batata/brocolis") == EOpSuccess) && (rmdir2("/batata/brocolis") == EOpSuccess))
	{
		result = TestSuccess;
	}
	else
	{
		result = TestError;
	}
	// Should not remove this one
	if ((result == TestSuccess) && (rmdir2("/batata/") != EOpSuccess))
	{
		result = TestSuccess;
	}
	else
	{
		result = TestError;
	}

	return result;
}