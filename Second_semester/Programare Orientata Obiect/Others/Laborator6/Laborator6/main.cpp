#include <iostream>
#include "Tests.h"
#include "Repo.h"
#include "Service.h"
#include "Console.h"

int main() {
    Tests tests;
    tests.runAll();
    /*
    Repo r;
    Service srv{ r };
    Console cns{ srv };
    cns.run();
    */
    return 0;
}
