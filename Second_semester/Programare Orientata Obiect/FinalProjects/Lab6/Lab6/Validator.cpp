#include "Validator.h"


void validator::validateName(string name) {
    if (name == "-1")
        throw ValidationError("invalid");
    if (name.empty())
        throw ValidationError("Niciun nume primit");
    if (name.find_first_of("0123456789") < string::npos)
        throw ValidationError("Numele nu poate contine valori numerice");

}

void validator::validateManufacturer(string manufacturer) {
    if (manufacturer == "-1")
        throw ValidationError("invalid");
    if (manufacturer.empty())
        throw ValidationError("Niciun producator primit");
    if (manufacturer.find_first_of("0123456789") < string::npos)
        throw ValidationError("Producatorul nu poate contine valori numerice");

}
void validator::validateSubstance(string substance) {
    if (substance == "-1")
        throw ValidationError("invalid");
    if (substance.empty())
        throw ValidationError("Nicio substanta primita");

}
void validator::validatePrice(string price) {
    if (price == "-1")
        throw ValidationError("invalid");
    if (price.empty())
        throw ValidationError("Niciun pret primit");

    if (price.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBN") < string::npos)
        throw ValidationError("Pretul nu poate contine litere");

}

void validator::validateAll(string name, string price, string manufacturer, string substance) {
    try {
        validateName(name);
        validatePrice(price);
        validateManufacturer(manufacturer);
        validateSubstance(substance);
    }
    catch (const ValidationError& e) {
        throw e;}
}