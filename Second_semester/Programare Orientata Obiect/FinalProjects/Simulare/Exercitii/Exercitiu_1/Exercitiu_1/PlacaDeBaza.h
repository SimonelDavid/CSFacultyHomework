//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_PLACADEBAZA_H
#define PARTIAL_RECAP_2_PLACADEBAZA_H
#include <string>
#include <utility>
using std::string;

class PlacaDeBaza {
private:
    string nume;
    string soclu;
public:
    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume) {
        PlacaDeBaza::nume = nume;
    }

    const string &getSoclu() const {
        return soclu;
    }

    void setSoclu(const string &soclu) {
        PlacaDeBaza::soclu = soclu;
    }

    int getPret() const {
        return pret;
    }

    void setPret(int pret) {
        PlacaDeBaza::pret = pret;
    }

private:
    int pret;
public:
    PlacaDeBaza(string nume, string soclu, int pret):
        nume{std::move(nume)},
        soclu{soclu},
        pret{pret}{};
    PlacaDeBaza& operator=(const PlacaDeBaza& other){
        if(this == &other)return *this;
        this->pret = other.pret;
        this->soclu = other.soclu;
        this->nume = other.nume;
        return *this;
    }

};


#endif //PARTIAL_RECAP_2_PLACADEBAZA_H
