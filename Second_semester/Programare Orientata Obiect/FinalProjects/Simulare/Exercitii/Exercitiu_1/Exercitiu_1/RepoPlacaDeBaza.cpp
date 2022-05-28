//
// Created by david on 17.05.2022.
//

#include <sstream>
#include <fstream>
#include "RepoPlacaDeBaza.h"

vector<PlacaDeBaza> &RepoPlacaDeBaza::getAll() {
    return all;
}

void RepoPlacaDeBaza::readFromFile() {
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
        string soclu = parts[1];
        int pret = stoi(parts[2]);
        PlacaDeBaza p{name, soclu, pret};
        all.push_back(p);
    }
    fin.close();
}

void RepoPlacaDeBaza::saveInFile() {
    std::ofstream aff(path);
    for(auto& p: all){
        aff<<p.getNume()<<","
           <<p.getSoclu()<<","
           <<p.getPret()<<",\n";
    }
    aff.close();
}

void RepoPlacaDeBaza::add(PlacaDeBaza &placa) {
    all.push_back(placa);
    saveInFile();
}
