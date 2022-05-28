#pragma once
#include "service.h"
#include "errors.h"
#include <iostream>

using namespace std;
class console{
typedef void(console::*comm)();
    private:
        service farmacie;
        service_reteta reteta = service_reteta(farmacie);
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

        void meniuReteta();

        void adaugaInReteta();

        void golesteReteta();

        void genereazaReteta();

        void exportReteta();

        void afiseazaRapoarte();
};