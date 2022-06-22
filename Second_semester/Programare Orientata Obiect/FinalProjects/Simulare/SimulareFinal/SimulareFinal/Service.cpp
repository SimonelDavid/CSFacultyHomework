//
// Created by david on 20.05.2022.
//

#include "Service.h"

Service::Service(Repo &repo) : repo(repo) {}

Candidat &Service::find(string id) {
    return repo.find(id);
}

vector<Candidat> Service::filterNume(string nume) {
    vector<Candidat> rezult;
    for(auto &c: repo.getAll()){
        if(c.getNume() == nume)
            rezult.push_back(c);
    }
    return rezult;
}
