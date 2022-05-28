//
// Created by david on 17.05.2022.
//

#include "Service.h"

#include <utility>

void Service::addPlaca(string nume, string soclu, int pret) {
    Candidat p{std::move(nume), std::move(soclu), pret};
    repoPlacaDeBaza.add(p);
}

vector<Candidat> Service::filterBySoclu(string name) {
    vector<Candidat> placi;
    string soclu;
    for(auto &placa : repoPlacaDeBaza.getAll()) {
        if (placa.getJob() == soclu)
            placi.push_back(placa);
    }
    return placi;
}

int Service::pret(string numeProcesor, string numePlaca) {
    int pret = 0;
    for(auto& placa: repoPlacaDeBaza.getAll()){
        if(numePlaca == placa.getNume()){
            return pret + placa.getPret();
        }
    }
    return 0;
}
