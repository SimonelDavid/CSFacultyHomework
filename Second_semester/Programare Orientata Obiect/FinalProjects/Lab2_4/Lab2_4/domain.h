#pragma once
#ifndef DOMAIN_H_
#define DOMAIN_H_



typedef struct {
	int data;
	int pret;
	char tip[15];
}Oferta;



typedef int(*Comparator)(Oferta* oferta1, Oferta* oferta2);

//Genereaza si returneaza o oferta
Oferta* createOferta(int data, int pret, char* tip);

Oferta* copyOferta(Oferta* oferta);

void deleteOferta(Oferta* oferta);

//Verifica daca doua cheltuieli sunt identice
int checkEqualOferte(Oferta* oferta1, Oferta* oferta2);
//Formateaza si afiseaza o oferta
void printOferta(Oferta* oferta);
//ERORI
//const int NO_ERROR = 1;
//const int ERROR_INVALID_INPUT = 2;
//const int ERROR_INVALID_ACCESS = 3;
//const int ERROR_NOT_FOUND = 4;

#endif // !DOMAIN_H_