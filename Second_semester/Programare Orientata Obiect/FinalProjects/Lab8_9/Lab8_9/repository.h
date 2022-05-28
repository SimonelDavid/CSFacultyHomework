#pragma once
#include "entity.h"
#include "errors.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

bool comparator_nume(entity a, entity b);


typedef pair<vector<entity>::iterator,vector<entity>::iterator> iter_pair;
typedef vector<entity>::iterator physical;


/*
    Class created to manage the repository of the application.
*/
class repository{
    private:
        vector<entity> list;
        int nrElems;
        
        //finds an element in the class
        //returns an iterator to the element
        physical find(unsigned int code) ;
    public:

        // constructor
        repository();

        //sees if provided code is valid
        bool test_code(int code) ;
        //returns a copy of the element at location pos
        entity getElem(int code);
        // adds an element to the class
        int addElem(entity to_add);

        // removes an element of the class
        void removeElem(int code);
        
        // changes the element at 'pos' with the
        // updated entity
        void changeElement(int code, entity updated);


        // returns the number of elements in the class
        int getNrElems();
        // returns a pair of references to the beginning and the 
        // end of the class' list
        iter_pair getAll();

        void DESTROY();

        void sortElems(int clause);
};

class repository_report{
    private:
        unordered_map<string, int> reports;
    public:

        void addItem(string manufacturer);

        int getItem(string manufacturer) const;

        void removeItem(string manufacturer);

        pair<unordered_map<string, int>::iterator, unordered_map<string, int>::iterator>
        getAll();
};