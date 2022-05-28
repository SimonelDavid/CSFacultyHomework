//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_REPOPLACADEBAZA_H
#define PARTIAL_RECAP_2_REPOPLACADEBAZA_H
#include <string>
#include "Candidat.h"
#include <vector>
using std::vector;
using std::string;

class RepoCandidati {
private:
    vector<Candidat> all;
    string path;
public:
    RepoCandidati(string path):path{std::move(path)}{readFromFile();};

    vector<Candidat>& getAll();
    void readFromFile();
    void saveInFile();
    void add(Candidat& candidat);
};


#endif //PARTIAL_RECAP_2_REPOPLACADEBAZA_H
