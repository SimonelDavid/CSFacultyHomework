#pragma once
#include "service.h"
#include "errors.h"
#include <iostream>

using namespace std;
class console {
    typedef void(console::* comm)();
private:
    service farmacie;
    vector<comm> functi;

    void afiseazaLista();
public:
    console();

    void adauga();

    void sterge();

    void modifica();

    void cautare();

    void afisare();

    void iesire();

    void filtrare();

    void sortare();

    void run();
};