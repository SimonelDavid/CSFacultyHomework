//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_PROCESOR_H
#define PARTIAL_RECAP_2_PROCESOR_H
#include <string>
#include <utility>
using std::string;

class Procesor {
private:
    string nume;
    int nrThreaduri;
public:
    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume) {
        Procesor::nume = nume;
    }

    int getNrThreaduri() const {
        return nrThreaduri;
    }

    void setNrThreaduri(int nrThreaduri) {
        Procesor::nrThreaduri = nrThreaduri;
    }

    const string &getSoclu() const {
        return soclu;
    }

    void setSoclu(const string &soclu) {
        Procesor::soclu = soclu;
    }

    int getPret() const {
        return pret;
    }

    void setPret(int pret) {
        Procesor::pret = pret;
    }

private:
    string soclu;
    int pret;
public:
    Procesor(string nume,
             int nrThreaduri,
             string soclu,
             int pret):nume{std::move(nume)},
             nrThreaduri{nrThreaduri},
             soclu{std::move(soclu)},
             pret{pret}{};
    Procesor& operator=(const Procesor& other){
        if(&other == this){
            return *this;
        }
        this->nume=other.nume;
        this->soclu = other.soclu;
        this->pret = other.pret;
        this->nrThreaduri = other.nrThreaduri;
        return *this;
    }
};


#endif //PARTIAL_RECAP_2_PROCESOR_H
