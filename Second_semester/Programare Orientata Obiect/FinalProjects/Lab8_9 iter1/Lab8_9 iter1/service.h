#pragma once
#include "repository.h"
#include "validator.h"
#include "errors.h"
#include <fstream>
#include <unordered_map>
using namespace std;


class service{
    private:
        repository repo; 
        validator valid;
        repository filter;
        repository_report rapoarte;
    public:

    // adds an element with the properties
    //  to the repository
    unsigned int addElem(string name, string price, string manufacturer, string substance);
    
    //deletes the element situated at 'pos'
    void deleteElem(int pos);
    // modifies the element at the location 'pos'
    void changeElem(int pos,string name, string price, string manufacturer, string substance );

    // returns a pair of references to the elements of the 
    // repository 
    iter_pair getAll();


    //gets the number of elements in the service
    int getNrElems();
    // searches the element with the transmited name or
    // manufacturer
    entity searchElem(string name, string manufacturer);


    // filters
    iter_pair filterElems_afterPrice(string price);
    iter_pair filterElems_afterSubstance(string substance);
    iter_pair filterElems_afterName(string name);

    iter_pair filterElems(string attr, int clause);


    void sortElems(int clause);

    entity getElem(int pos);

    pair<unordered_map<string, int>::iterator,unordered_map<string, int>::iterator> getReports();
};


class service_reteta{

    private:
        service& serv;
        repository lista;
    public:
        
        service_reteta(service& s):serv(s) {};

        //adauga medicamentul cu numele nume din repo in reteta
        void adaugaPeReteta(string nume);

        //goleste reteta
        void golesteReteta();

        //genereaza o reteta cu nrTotal de medicamente
        void genereazaReteta(int nrTotal);


        //exporta reteta intr-un fisier cu numele transmis
        //ca parametru
        void exportReteta(string numeFisier);
};












