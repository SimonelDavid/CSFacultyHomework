//
// Created by david on 17.05.2022.
//

#include <fstream>
#include "Tests.h"

void Tests::repoTests() {

}

void Tests::srvTests() {

}

void Tests::reloadFiles() {
    std::ofstream placi("placi.txt");
    for(int i = 1; i < 10; i++){
        placi<<i<<","
                  <<(i+3)%7<<","
                  <<i<<",\n";
    }
    placi.close();
}

void Tests::runAll() {
    reloadFiles();
    repoTests();
    srvTests();
}
