#include <string>
#include <vector>
#include "Locatar.h"
/*
Scrie in fisierul fName lista de locatari
in format Comma Separated Values
arunca exceptie daca nu poate crea fisierul
*/
void exportToCVS(const std::string& fName, const std::vector<Locatar>& loc);
/*
Scrie in fisierul fName lista de locatari
in format HTML
arunca exceptie daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fName, const std::vector<Locatar>& loc);