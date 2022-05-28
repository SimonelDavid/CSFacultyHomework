#include "Service.h"

#include <utility>

void Service::addCandidat(string nume, string job, string status) {
    Candidat p{std::move(nume), std::move(job), status};
    repoCandidati.add(p);
}

vector<Candidat> Service::filterByName(string name) {
    vector<Candidat> candidati;
    string nume;
    for(auto &candidat : repoCandidati.getAll()) {
        if (candidat.getNume() == nume)
            candidati.push_back(candidat);
    }
    return candidati;
}