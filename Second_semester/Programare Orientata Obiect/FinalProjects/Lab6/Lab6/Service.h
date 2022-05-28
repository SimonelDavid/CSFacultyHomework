#pragma once
#include "Repository.h"
#include "Validator.h"
#include "Errors.h"

using namespace std;


class service {
private:
    repository repo;
    validator valid;
    repository filter;
public:

    // adds an element with the properties
    //  to the repository
    void addElem(string name, string price, string manufacturer, string substance);

    //deletes the element situated at 'pos'
    void deleteElem(int pos);
    // modifies the element at the location 'pos'
    void changeElem(int pos, string name, string price, string manufacturer, string substance);

    // returns a pair of references to the elements of the 
    // repository 
    iter_pair getAll();


    //gets the number of elements in the service
    int getNrElems() noexcept;
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

};