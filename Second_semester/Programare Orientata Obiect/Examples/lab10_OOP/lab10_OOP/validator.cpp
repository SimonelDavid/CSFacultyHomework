#include "validator.h"
#include <assert.h>
#include <sstream>

ostream& operator<<(ostream& out, const ValidateException& ex)
{
    for (const auto& msg : ex.msgs) {
        out << msg << " ";
    }
    return out;
}

void LocatarValidator::validate(const Locatar& l)
{
    vector < string> msgs;
    if (l.getApartment() < 0) msgs.push_back("Numar apartament negativ");
    if (l.getSurface() < 0) msgs.push_back("Suprafata negativa");
    if (l.getName().size() < 0) msgs.push_back("Nume vid");
    if (l.getType().size() < 0) msgs.push_back("Tip vid");
    if (msgs.size() > 0) {
        throw ValidateException(msgs);
    }
}

void testValidate() {
    LocatarValidator v;
    Locatar l{ -1,"",-1,"" };
    try {
        v.validate(l);
    }
    catch (const ValidateException& ex) {
        std::stringstream sout;
        sout << ex;
        auto mesaj = sout.str();
        assert(mesaj.find("negativ") >= 0);
        assert(mesaj.find("vid") >= 0);
    }
}