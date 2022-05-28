#pragma once
#include "errors.h"
#include <string>
using namespace std;

class validator{

    public:
        void validateName(string name);

        void validatePrice(string price);

        void validateManufacturer(string manufacturer);

        void validateSubstance(string substance);

        void validateAll(string name, string price, string manufacturer, string substance);
};
