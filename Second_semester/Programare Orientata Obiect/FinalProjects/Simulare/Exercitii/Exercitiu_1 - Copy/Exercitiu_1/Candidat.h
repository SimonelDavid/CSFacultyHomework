//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_PLACADEBAZA_H
#define PARTIAL_RECAP_2_PLACADEBAZA_H
#include <string>
#include <utility>
using std::string;

class Candidat {
private:
    string nume;
    string job;
public:
    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume) {
        Candidat::nume = nume;
    }

    const string &getJob() const {
        return job;
    }

    void setJob(const string &job) {
        Candidat::job = job;
    }

    int getPret() const {
        return pret;
    }

private:
    int pret;
public:
    Candidat(string nume, string job, int pret):
        nume{std::move(nume)},
        job{job},
        pret{pret}{};
    Candidat& operator=(const Candidat& other){
        if(this == &other)return *this;
        this->pret = other.pret;
        this->job = other.job;
        this->nume = other.nume;
        return *this;
    }

};


#endif //PARTIAL_RECAP_2_PLACADEBAZA_H
