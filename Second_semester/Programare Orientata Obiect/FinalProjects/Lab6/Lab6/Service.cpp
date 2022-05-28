#include "Service.h"
#include <algorithm>


void service::addElem(string name, string price, string manufacturer, string substance) {
    try {
        valid.validateAll(name, price, manufacturer, substance);
    }
    catch (const ValidationError& e) {
        throw e;}
    entity to_add(name, stof(price), manufacturer, substance);

    repo.addElem(to_add);
}

void service::deleteElem(int pos) {
    if (pos < repo.getNrElems())
        repo.removeElem(pos);
    else {
        throw RangeError("Index out of range");}

}

void service::changeElem(int pos, string name, string price, string manufacturer, string substance) {

    if (pos > repo.getNrElems()) 
        throw RangeError("Index out of range");
    else {
        entity modif("", 0, "", "");
        entity actual = repo.getElem(pos);
        try {
            valid.validateName(name);
            modif.setName(name);
        }
        catch (const ValidationError& e) {
            throw e;}

        try {
            valid.validatePrice(price);
            modif.setPrice(stof(price));
        }
        catch (const ValidationError& e) {
            throw e;}

        try {
            valid.validateName(manufacturer);
            modif.setManufacturer(manufacturer);
        }
        catch (const ValidationError& e) {
            throw e;}

        try {
            valid.validateName(substance);
            modif.setSubstance(substance);
        }
        catch (const ValidationError& e) {
            throw e;}

        repo.changeElement(pos, modif);
    }

}


iter_pair service::getAll() {
    return repo.getAll();
}

int service::getNrElems() noexcept {
    return repo.getNrElems();
}


entity service::searchElem(string name, string manufacturer) {
    iter_pair meds = repo.getAll();
    for (; meds.first != meds.second; ++meds.first) {
        if (name == meds.first->getName() && manufacturer == meds.first->getManufacturer()) {
            return *(meds.first);
        }
    }
    throw RangeError("No element found");}

iter_pair service::filterElems_afterPrice(string price) {

    try {
        valid.validatePrice(price);
        filter.DESTROY();
    }
    catch (const ValidationError& e) {
        throw e;}

    const float p = stof(price);


    iter_pair const res = repo.getAll();
    physical start = res.first;
    physical const end = res.second;


    for (; start != end; ++start) {
        if (start->getPrice() == p) {
            filter.addElem(*(start));
        }
    }

    return filter.getAll();
}


iter_pair service::filterElems_afterSubstance(string substance) {

    try {
        valid.validateSubstance(substance);
        filter.DESTROY();
    }
    catch (const ValidationError& e) {
        throw e;}

    iter_pair const res = repo.getAll();
    physical start = res.first;
    physical const end = res.second;


    for (; start != end; ++start) {
        if (start->getSubstance() == substance) {
            filter.addElem(*(start));
        }
    }

    return filter.getAll();
}

iter_pair service::filterElems_afterName(string name) {

    try {
        valid.validateName(name);
        filter.DESTROY();
    }
    catch (const ValidationError& e) {
        throw e;}

    iter_pair const res = repo.getAll();
    physical start = res.first;
    physical const end = res.second;


    for (; start != end; ++start) {
        if (start->getName() == name) {
            filter.addElem(*(start));
        }
    }
    return filter.getAll();
}

iter_pair service::filterElems(string attr, int clause) {
    switch (clause)
    {
    case 1:
        try {
            return filterElems_afterName(attr);
        }
        catch (const ValidationError& e) {
            throw e;}

    case 2:
        try {
            return filterElems_afterPrice(attr);
        }
        catch (const ValidationError& e) {
            throw e;}
    case 3:
        try {
            return filterElems_afterSubstance(attr);
        }
        catch (const ValidationError& e) {
            throw e;}
    default:
        throw RangeError("Invalid crit.");}}

void service::sortElems(int clause) {
    repo.sortElems(clause);
}

entity service::getElem(int pos) {
    return repo.getElem(pos);
}