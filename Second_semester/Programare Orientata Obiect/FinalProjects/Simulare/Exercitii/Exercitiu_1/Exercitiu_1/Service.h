//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_SERVICE_H
#define PARTIAL_RECAP_2_SERVICE_H


#include "RepoProcesor.h"
#include "RepoPlacaDeBaza.h"

class Service {
private:
    RepoProcesor& repoProcesoare;
    RepoPlacaDeBaza& repoPlacaDeBaza;
public:
    Service(RepoProcesor& repoProcesor,
            RepoPlacaDeBaza& repoPlacaDeBaza):
            repoPlacaDeBaza{repoPlacaDeBaza},
            repoProcesoare{repoProcesor}{};

    vector<Procesor>& getProcesoare(){
        return repoProcesoare.getAll();
    };
    vector<PlacaDeBaza>& getPlaciDeBaza(){
        return repoPlacaDeBaza.getAll();
    }
    void addPlaca(string nume,
                  string soclu,
                  int pret);

    vector<PlacaDeBaza> filterBySoclu(string name);
    int pret(string numeProcesor, string numePlaca);
};


#endif //PARTIAL_RECAP_2_SERVICE_H
