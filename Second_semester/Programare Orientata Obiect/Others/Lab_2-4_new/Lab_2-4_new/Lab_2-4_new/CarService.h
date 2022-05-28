#pragma once

#include "CarsRepository.h"

typedef struct 
{
	MyList* allCars;
	MyList* undoList;
} CarStore;

/*
  create a carstore for rent
*/
CarStore createCarStore();

void destroyStore(CarStore* store);
/*
Add a car to the store
*/
int addCar(CarStore* store,int numar_inmatriculare, char* model, char* categorie);

/*
  Filter cars in the store
  typeSubstring - cstring
  return all cars where typeSubstring is a substring of the type
*/
MyList* getAllCars(CarStore* store);

/*
Sort ascending by type
*/
MyList* sortByModel(CarStore* store);

/*
Sort ascending by species
*/
MyList* sortByCategories(CarStore* store);

int undo(CarStore* store);

int changeInchiriereCar(CarStore* store, int numar_inmatriculare);


void testAddCar();
void testAddInvalidCar();
void testSorts();
void testModifyCar();
void testchangeInchiriereCar();

int modifyCar(CarStore* store, int numar_inmatriculare, char* modelnou, char* categorienoua);
