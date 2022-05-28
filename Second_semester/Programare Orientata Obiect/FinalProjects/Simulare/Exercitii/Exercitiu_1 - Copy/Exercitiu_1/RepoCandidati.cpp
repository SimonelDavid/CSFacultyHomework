#include <sstream>
#include <fstream>
#include "RepoCandidati.h"

vector<Candidat> &RepoCandidati::getAll() {
    return all;
}

void RepoCandidati::readFromFile() {
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
        Candidat p{name, soclu, pret};
        all.push_back(p);
    }
    fin.close();
}

void RepoCandidati::saveInFile() {
    std::ofstream aff(path);
    for(auto& p: all){
        aff<<p.getNume()<<","
           <<p.getJob()<<","
           <<p.getPret()<<",\n";
    }
    aff.close();
}

void RepoCandidati::add(Candidat &placa) {
    all.push_back(placa);
    saveInFile();
}
