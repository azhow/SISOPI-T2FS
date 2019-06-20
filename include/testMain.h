#ifndef TESTMAIN_H
#define TESTMAIN_H

#include "ETestStatus.h"

// Run all tests
ETestStatus runAllTests();

// readdir2 function test
ETestStatus testReaddir2();

// opendir2 function test
ETestStatus testOpendir2();

// format2 function test
ETestStatus testFormat2();

// closedir2 function test
ETestStatus testClosedir2();

// bitmap functions test
ETestStatus testBitmap();

// chdir2 function test
ETestStatus testChdir2();

// getcwd2 function test
ETestStatus testGetcwd2();

// open2 function test
ETestStatus testOpen2();

// create2 function test
ETestStatus testCreate2();

#endif // !TESTMAIN_H