#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "TestScurt.h"
#include "TestExtins.h"

using namespace std;

int main() {
	test_funct_noua();
	testAll();
	testAllExtins();
	cout << "Finished tests! \n";
	_CrtDumpMemoryLeaks();
	return 0;
}