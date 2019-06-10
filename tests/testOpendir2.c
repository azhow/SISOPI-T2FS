#include "TestOpendir2.h"

ETestStatus testOpendir2()
{
	char testPath[] = "/";
	opendir2(testPath);

	return TestSuccess;
}