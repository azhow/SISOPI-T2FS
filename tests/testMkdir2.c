#include "testMain.h"
#include "ETestStatus.h"
#include "EOperationStatus.h"
#include "t2fs.h"

// mkdir2 function test
ETestStatus testMkdir2()
{
	ETestStatus result = TestError;

	if (mkdir2("/batata") == EOpSuccess)
	{
		result = TestSuccess;
	}
	else
	{
		result = TestError;
	}
	if (mkdir2("/batata/feijao") == EOpSuccess)
	{
		result = TestSuccess;
	}
	else
	{
		result = TestError;
	}
	if ((chdir2("/batata/") == EOpSuccess) && (mkdir2("./arroz") == EOpSuccess))
	{
		result = TestSuccess;
	}
	else
	{
		result = TestError;
	}

	return result;
}