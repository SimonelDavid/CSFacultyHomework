//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_REPOPLACADEBAZA_H
#define PARTIAL_RECAP_2_REPOPLACADEBAZA_H
#include <string>
#include "PlacaDeBaza.h"
#include <vector>
using std::vector;
using std::string;

class RepoPlacaDeBaza {
private:
    vector<PlacaDeBaza> all;
    string path;
public:
    RepoPlacaDeBaza(string path):path{std::move(path)}{readFromFile();};

    vector<PlacaDeBaza>& getAll();
    void readFromFile();
    void saveInFile();
    void add(PlacaDeBaza& placaDeBaza);
};


#endif //PARTIAL_RECAP_2_REPOPLACADEBAZA_H
