//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_SERVICE_H
#define PARTIAL_RECAP_2_SERVICE_H

#include "RepoCandidati.h"

class Service {
private:
    RepoCandidati& repoPlacaDeBaza;
public:
    Service(RepoCandidati& repoPlacaDeBaza):repoPlacaDeBaza{repoPlacaDeBaza}{};

    vector<Candidat>& getPlaciDeBaza(){
        return repoPlacaDeBaza.getAll();
    }
    void addPlaca(string nume,
                  string soclu,
                  int pret);

    vector<Candidat> filterBySoclu(string name);
    int pret(string numeProcesor, string numePlaca);
};


#endif //PARTIAL_RECAP_2_SERVICE_H
