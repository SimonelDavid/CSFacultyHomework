#pragma once
typedef struct {
	int numar_inmatriculare;
	char* model;
	char* categorie;
	int inchiriata;
} Car;

/*
Create a new car
*/
Car* createCar(int numar_inmatriculare, char* model, char* categorie);

/*
 Dealocate memory occupied by car
*/
void destroyCar(Car* p);

void set_model(Car* masina, char* model);

void set_categorie(Car* masina, char* categorie);

void set_inchiriata(Car* masina, int inchiriata);

int masini_egale(Car* masina1, Car* masina2);

int validare_categorie(char* categorie);

int validare_masina(Car* masina);

void testare_validare_masina();

/*
Create a copy for the car
Deep copy - copy all the sub-parts
*/
Car* copyCar(Car* p);

void testCreateDestroy();

