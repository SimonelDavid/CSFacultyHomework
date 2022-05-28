#pragma once
#include "Entity.h"
#include "VectorDinamic.h"
#include "Validator.h"

bool comparator_nume(entity a, entity b);


typedef pair<Lista<entity>::iterator, Lista<entity>::iterator> iter_pair;
typedef Lista<entity>::iterator physical;


/*
    Class created to manage the repository of the application.
*/
class repository {
private:

    Lista<entity> list;
    int nrElems;

    //finds an element in the class
    //returns an iterator to the element
    physical find(int pos);
public:

    // constructor
    repository() noexcept;

    //returns a copy of the element at location pos
    entity getElem(int pos);
    // adds an element to the class
    void addElem(entity to_add);

    // removes an element of the class
    void removeElem(int pos);

    // changes the element at 'pos' with the
    // updated entity
    void changeElement(int pos, entity updated);


    // returns the number of elements in the class
    int getNrElems() noexcept;
    // returns a pair of references to the beginning and the 
    // end of the class' list
    iter_pair getAll();

    void DESTROY();

    void sortElems(int clause);

};
