#include "Entity.h"
#include <iostream>
using namespace std;

entity::entity(string d, float p, string prod, string subst) :
    name{ d }, price{ p }, manufacturer{ prod }, substance{ subst }{};

entity::entity(const entity& copy) :
    name{ copy.getName() }, price{ copy.getPrice() }, manufacturer{ copy.getManufacturer() }, substance{ copy.getSubstance() }{}


string entity::getName() const {
    return name;
}
float entity::getPrice() const noexcept {
    return price;
}
string entity::getManufacturer() const {
    return manufacturer;
}
string entity::getSubstance() const {
    return substance;
}

void entity::setName(const string attr) {
    name = attr;
}
void entity::setPrice(const float attr) noexcept {
    price = attr;
}
void entity::setManufacturer(const string attr) {
    manufacturer = attr;
}
void entity::setSubstance(const string attr) {
    substance = attr;
}

bool entity::operator==(const entity& a) {
    return name == a.getName() && manufacturer == a.getManufacturer();
}

entity& entity::operator=(const entity& a) {
    name = a.getName();
    price = a.getPrice();
    manufacturer = a.getManufacturer();
    substance = a.getSubstance();

    return *this;
}

const string entity::getAfis() const {
    string afis;
    afis += "Numele medicamentului este: ";
    afis += name;
    afis += '\n';
    afis += "Pretul medicamentului este: ";
    afis += to_string(price);
    afis += '\n';
    afis += "Producatorul medicamentului este: ";
    afis += manufacturer;
    afis += '\n';
    afis += "Substanta activa a medicamentului este: ";
    afis += substance;
    afis += '\n';

    return afis;
}