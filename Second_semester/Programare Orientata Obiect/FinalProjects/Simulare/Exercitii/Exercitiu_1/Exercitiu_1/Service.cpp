//
// Created by david on 17.05.2022.
//

#include "Service.h"

#include <utility>

void Service::addPlaca(string nume, string soclu, int pret) {
    PlacaDeBaza p{std::move(nume), std::move(soclu), pret};
    repoPlacaDeBaza.add(p);
}

vector<PlacaDeBaza> Service::filterBySoclu(string name) {
    vector<PlacaDeBaza> placi;
    string soclu;
    for(auto &procesor: repoProcesoare.getAll()){
        if(procesor.getNume()==name){
            soclu = procesor.getSoclu();
            break;
        }
    }
    for(auto &placa : repoPlacaDeBaza.getAll()) {
        if (placa.getSoclu() == soclu)
            placi.push_back(placa);
    }
    return placi;
}

int Service::pret(string numeProcesor, string numePlaca) {
    int pret = 0;
    for(auto& procesor: repoProcesoare.getAll()) {
        if (numeProcesor == procesor.getNume()) {
            pret += procesor.getPret();
            break;
        }
    }
    for(auto& placa: repoPlacaDeBaza.getAll()){
        if(numePlaca == placa.getNume()){
            return pret + placa.getPret();
        }
    }
    return 0;
}
