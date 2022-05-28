//
// Created by david on 17.05.2022.
//

#include <fstream>
#include <sstream>
#include "RepoProcesor.h"

void RepoProcesor::readFromFile() {
    all.clear();
    std::ifstream fin(path);
    string line;
    while(fin>>line){
        std::stringstream stringstream(line);
        string part;
        vector<string>parts;
        while (std::getline(stringstream, part, ',')){
            parts.push_back(part);
        }
        string name = parts[0];
        int nrThreaduri = stoi(parts[1]);
        string soclu = parts[2];
        int pret = stoi(parts[3]);
        Procesor p{name, nrThreaduri, soclu, pret};
        all.push_back(p);
    }
    fin.close();
}

void RepoProcesor::saveInFile() {
    std::ofstream aff(path);
    for(auto& p: all){
        aff<<p.getNume()<<","
            <<p.getNrThreaduri()<<","
            <<p.getSoclu()<<","
            <<p.getPret()<<",\n";
    }
    aff.close();
}

vector<Procesor> &RepoProcesor::getAll() {
    return all;
}
