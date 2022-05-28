#pragma once
//#ifndef MASINA_H_
//#define MASINA_H_

typedef struct {
	int numar_inmatriculare;
	char* model;
	char* categorie;
	int inchiriata;
}Car;


/*
Create a new car
*/
Car createCar(int numar_inmatriculare, char* model, char* categorie);


int masini_egale(Car masina1, Car masina2);


/*
 Dealocate memory occupied by car
*/
void destroyCar(Car* masina);

//---
void set_nr_inmatriculare(Car* masina, int nr_inamtriculare);

void set_model(Car* masina, char* model);

void set_categorie(Car* masina, char* categorie);

void set_inchiriata(Car* masina, int inchiriata);


//---


/*
Create a copy for the car
Deep copy - copy all the sub-parts
*/
Car copyCar(Car* masina);

/*
   Validate car
   return !=0 if car is invalid
*/
int validare_categorie(char* categorie);
int validare_masina(Car masina);

//void testCreateDestroy();

void testare_CreeazaDistruge_masina();

void testare_validare_masina();


