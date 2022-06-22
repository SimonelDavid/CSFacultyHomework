//
// Created by david on 20.05.2022.
//

#include <fstream>
#include "Tests.h"
#include <cassert>
#include <iostream>
#include "Repo.h"
#include "Service.h"

void Tests::runAll() {
    initFiles();
    repoTests();
    srvTests();
    initFiles();
    std::cout<<"tests ok\n";
}

void Tests::initFiles() {
    std::ofstream aff("cand.txt");
    for(int i = 0; i < 10; i++){
        aff<<i%5<<","<<i<<","<<"pending"<<","<<i<<",\n";
    }
    aff.close();
}

void Tests::repoTests() {
    ///testare crud
    Repo r{"cand.txt"};
    assert(r.getAll().size() == 10);
    Candidat c{"foo", "foo", "foo", "0"};
    r.mod(c);
    assert(r.getAll()[0].getNume()=="foo" && r.getAll()[0].getCandidatura() == "foo" && r.getAll()[0].getJob() == "foo");
    assert(r.find("0").getNume() == "foo");
}

void Tests::srvTests() {
    ///testare crud
    Repo r{"cand.txt"};
    Service s{r};
    assert(s.getAll().size() ==10);
    s.mod("0", "foo", "foo", "foo");
    assert(s.getAll()[0].getNume()=="foo" && s.getAll()[0].getCandidatura() == "foo" && s.getAll()[0].getJob() == "foo");
    assert(s.find("0").getNume() == "foo");

    //testare filtru
    vector<Candidat> result = s.filterNume("inexistent");
    assert(result.empty());
    result = s.filterNume("2");
    for(auto& c: result)assert(c.getNume()=="2");

}
