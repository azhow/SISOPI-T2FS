// We use this to avoid multiple main definitions
#ifdef TEST
// Here we call the runAllTests function defined in testMain
#include <stdio.h>
#include "testMain.h"

int main(int argc, char* argv[])
{
	// Just call the run all tests and if it returns != there's error
	return runAllTests();
}
#else
#include <stdio.h>

int main(int argc, char* argv[])
{
	return 0;
}

#endif