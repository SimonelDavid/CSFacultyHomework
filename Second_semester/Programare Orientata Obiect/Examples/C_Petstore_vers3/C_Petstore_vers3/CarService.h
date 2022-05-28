#pragma once

#include "CarRepository.h"

typedef struct {
	MyList* allCars;
	MyList* undoList;//list of list of pets
} CarStore;

/*
  create a petstore
*/
CarStore createCarStore();

void destroyStore(CarStore* store);
/*
Add a car to the store
*/
int addCar(CarStore* store, int numar_inmatriculare, char* model, char* categorie);

/*
  Filter pets in the store 
  typeSubstring - cstring
  return all pets where typeSubstring is a substring of the model
*/
MyList* getAllCars(CarStore* store, char* typeSubstring);

int modifyCar(CarStore* store, int numar_inmatriculare, char* modelnou, char* categorienoua);

int changeInchiriereCar(CarStore* store, int numar_inmatriculare, int set_status);

/*
Sort ascending by model
*/
MyList* sortByModel(CarStore* store);

/*
Sort ascending by categorie
*/
MyList* sortByCategories(CarStore* store);

/*
Restore previous car list
return 0 on ok, 1 if there is no more available undo
*/
int undo(CarStore* store);

void testModify();
void testAddInvalidCar();
void testAddCar();
void testSorts();
void testUndo();
void testInchiriat();
