//
// Created by david on 20.05.2022.
//

#include "Repo.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile() {
    all.clear();
    std::ifstream fin(filePath);
    string line;
    while(fin>>line){
        std::stringstream ss;
        ss<<line;
        string buf;
        vector<string>parts;
        while(std::getline(ss, buf, ','))
            parts.push_back(buf);
        Candidat candidat{parts[0], parts[1], parts[2], parts[3]};
        all.push_back(candidat);
    }
    fin.close();
}

void Repo::mod(Candidat &nou) {
    for(int i = 0; i < all.size(); i++){
        if(all[i] == nou) {
            all[i] = nou;
            return;
        }
    }
}
