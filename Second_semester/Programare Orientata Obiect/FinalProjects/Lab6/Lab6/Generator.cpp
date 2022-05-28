#include "Generator.h"
#include <iostream>

string generator::genString() {

    const char alpha[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"; // NOLINT
    string gen = "";
    for (int i = 0; i < SIZE; ++i) {
        gen += alpha[(int)(rand() % 52)]; // NOLINT
    }

    return gen;
}

float generator::genFloat() {
    return (float)(rand() % 1000);
}


entity generator::genEntity() {
    string name = genString();
    const float price = genFloat();
    string manufacturer = genString();
    string substance = genString();


    entity a(name, price, manufacturer, substance);

    return a;
}