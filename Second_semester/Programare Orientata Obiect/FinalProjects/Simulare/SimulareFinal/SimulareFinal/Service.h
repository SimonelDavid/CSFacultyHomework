//
// Created by david on 20.05.2022.
//

#ifndef SIMULARE_SERVICE_H
#define SIMULARE_SERVICE_H


#include "Repo.h"

class Service {
private:
    Repo& repo;
public:
    Service(Repo &repo);
    /*
     * da toata lista de candidati
     */
    vector<Candidat>& getAll(){return repo.getAll();};
    /*
     * modifica candidatul cu id cu noul nume, job sau statuts
     */
    void mod(string id, string nume, string job, string cand){
        Candidat c{nume, job, cand, id};
      repo.mod(c);
    };
    Candidat& find(string id);

    /*
     * filtreaza dupa nume
     */
    vector<Candidat> filterNume(string nume);
};


#endif //SIMULARE_SERVICE_H
