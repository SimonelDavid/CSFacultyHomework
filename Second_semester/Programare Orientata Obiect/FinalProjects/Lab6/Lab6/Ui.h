#pragma once
#include "Service.h"
#include "Errors.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class console {
    // typedef void(console::&comm)();
private:
    service farmacie;

    void afiseazaLista();
public:
    // console();

    void adauga();

    void sterge();

    void modifica();

    void cautare();

    void afisare();

    void iesire() noexcept;

    void filtrare();

    void sortare();

    void run();
};