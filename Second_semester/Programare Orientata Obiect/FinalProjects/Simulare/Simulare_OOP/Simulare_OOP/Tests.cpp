#include <fstream>
#include "Tests.h"

void Tests::repoTests() {

}

void Tests::srvTests() {

}

void Tests::reloadFiles() {
    std::ofstream candidati("candidati.txt");
        candidati<<"Gigel" << "," << "inginer_electronist" << "," << "hired" << ",\n";
        candidati << "Alexandra" << "," << "inginer_software" << "," << "pending" << ",\n";
        candidati << "Mihai" << "," << "vanzator" << "," << "rejected" << ",\n";
    candidati.close();
}

void Tests::runAll() {
    reloadFiles();
    repoTests();
    srvTests();
}
