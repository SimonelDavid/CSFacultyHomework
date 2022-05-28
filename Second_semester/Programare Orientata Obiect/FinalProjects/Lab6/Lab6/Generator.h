#pragma once
#define SIZE 50
#include "Entity.h"
#include <string>


/*Clasa de generare automata a entitatilor.*/
using namespace std;

class generator {
private:
public:
    string genString();
    float genFloat();

    entity genEntity();

};