//
// Created by david on 20.05.2022.
//

#ifndef SIMULARE_REPO_H
#define SIMULARE_REPO_H
#include "Candidat.h"
#include <utility>
#include <vector>
#include <stdexcept>
using std::vector;

class Repo {
private:
    vector<Candidat> all;
    string filePath;
    void loadFromFile();
public:
    /*
     * filePath e calea spre fisierul de import
     */
    Repo(string path):filePath(std::move(path)){loadFromFile();};
    /*
     * returneaza lista cu toti candidatii
     */
    vector<Candidat>& getAll(){return all;};
    ///modifica candidatul corespunzator cu cel nou
    void mod(Candidat& nou);

    ///cauta dupa id arunca exceptie daca nu gaseste
    Candidat& find(string id){
        for(int i = 0; i < all.size(); i++)
            if(all[i].getId() == id)return all[i];
        throw std::runtime_error("nu este");
    };
};


#endif //SIMULARE_REPO_H
