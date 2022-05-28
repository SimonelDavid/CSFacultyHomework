#ifndef SIMULARE_SERVICE_H
#define SIMULARE_SERVICE_H

#include "RepoCandidati.h"

class Service {
private:
    RepoCandidati& repoCandidati;
public:
    Service(RepoCandidati& repoCandidati):repoCandidati{repoCandidati}{};

    vector<Candidat>& getCandidati(){
        return repoCandidati.getAll();
    }
    void addCandidat(string nume,
                  string job,
                  string status);

    vector<Candidat> filterByName(string name);
};


#endif //SIMULARE_SERVICE_H
