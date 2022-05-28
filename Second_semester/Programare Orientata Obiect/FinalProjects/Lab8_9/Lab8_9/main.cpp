#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Tests.h"
#include "ui.h"

int main(){
    run_all_tests();

//    console app;
//    app.run();
    
    _CrtDumpMemoryLeaks();
    return 0;
}