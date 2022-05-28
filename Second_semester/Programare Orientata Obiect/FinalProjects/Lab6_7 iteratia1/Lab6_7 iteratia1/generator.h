#pragma once
#include "entity.h"
#include <string>


/*Clasa de generare automata a entitatilor.*/
using namespace std;

const int SIZE = 50;

class generator {
private:
public:
    string genString();
    float genFloat();

    entity genEntity();

};