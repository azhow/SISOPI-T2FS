#include "TestExample.h"
#include "ETestStatus.h"

ETestStatus testExampleSuccess()
{
	return TestSuccess;
}

ETestStatus testExampleFailure()
{
	return TestError;
}