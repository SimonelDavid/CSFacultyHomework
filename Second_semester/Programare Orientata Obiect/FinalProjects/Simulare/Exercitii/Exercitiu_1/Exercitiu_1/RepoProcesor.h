//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_REPOPROCESOR_H
#define PARTIAL_RECAP_2_REPOPROCESOR_H
#include <utility>
#include <vector>
#include "Procesor.h"

using std::vector;

class RepoProcesor {
private:
    vector<Procesor> all;
    string path;
public:
    RepoProcesor(string path):path{std::move(path)}{readFromFile();};

    vector<Procesor>& getAll();
    void readFromFile();
    void saveInFile();
};


#endif //PARTIAL_RECAP_2_REPOPROCESOR_H
