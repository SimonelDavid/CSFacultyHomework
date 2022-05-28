#include "CarService.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mysort.h"
/*
Add a car to the store
*/
int addCar(CarStore* store, int numar_inmatriculare, char* model, char* categorie) {
	Car* p = createCar(numar_inmatriculare, model, categorie);
	int errorCode = validare_masina(p);
	if (errorCode == 0)
	{
		destroyCar(p);
		return errorCode;
	}
	MyList* toUndo = copyList(store->allCars, copyCar);
	add(store->allCars, p);
	//add to undolist
	add(store->undoList, toUndo);
	return 0; // all ok
}

/*
  Restore previous car list
  return 0 on ok, 1 if there is no more available undo
*/
int undo(CarStore* store) {
	if (size(store->undoList) == 0) {
		return 1;//no more undo
	}
	MyList* l = removeLast(store->undoList);
	destroyList(store->allCars);
	store->allCars = l;
	return 0;
}

/*
Filter pets in the store
typeSubstring - cstring
return all pets where typeSubstring is a substring of the model
*/
MyList* getAllCars(CarStore* store, char* typeSubstring) {
	if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
		return copyList(store->allCars,copyCar);
	}
	MyList* masina = createEmpty(destroyCar);
	for (int i = 0; i < size(store->allCars); i++) {
		Car* p = get(store->allCars, i);
		if (strstr(p->model, typeSubstring) != NULL) {
			add(masina,copyCar (p));
		}
	}
	return masina;
}

int modifyCar(CarStore* store, int index, char* modelnou, char* categorienoua)
{
	// gasesc elem de inloc
	if (index == -1) return 0;
	ElemType elem = get(store->allCars, index);
	set_model(elem, modelnou);
	set_categorie(elem, categorienoua);
	set(store->allCars, index, elem); // store[i] = elem;
	return 1; // cod ok
}

int changeInchiriereCar(CarStore* store, int index, int set_status)
{
	if (index == -1) return 0;
	ElemType elem = get(store->allCars, index);
	set_inchiriata(elem, set_status);
	set(store->allCars, index, elem);
	return 1 + set_status;
}


int cmpModel(Car* p1, Car* p2) {
	return strcmp(p1->model, p2->model);
}

int cmpCategorie(Car* p1, Car* p2) {
	return strcmp(p1->categorie, p2->categorie);
}

/*
 Sort ascending by model
*/
MyList* sortByModel(CarStore* store) {
	MyList* l = copyList(store->allCars,copyCar);
	sort(l, cmpModel);
	return l;
}

/*
Sort ascending by categorie
*/
MyList* sortByCategories(CarStore* store) {
	MyList* l = copyList(store->allCars, copyCar);
	sort(l, cmpCategorie);
	return l;
}

CarStore createCarStore()
{
	CarStore masina;
	masina.allCars = createEmpty(destroyCar);
	masina.undoList = createEmpty(destroyList);
	return masina;
}

void destroyStore(CarStore * store)
{
	destroyList(store->allCars);
	destroyList(store->undoList);
}

void testAddCar() {
	CarStore store = createCarStore();
	addCar(&store, 100, "Audi", "suv");
	addCar(&store, 200, "Skoda", "altele");
	MyList* filtered = getAllCars(&store, NULL);
	assert(size(filtered) == 2);
	destroyList(filtered);

	filtered = getAllCars(&store, "Skoda");
	assert(size(filtered) == 1);
	destroyList(filtered);

	filtered = getAllCars(&store, "Audi");
	assert(size(filtered) == 1);
	destroyList(filtered);

	filtered = getAllCars(&store, "BMW");
	assert(size(filtered) == 0);
	destroyList(filtered);

	destroyStore(&store);
}

void testAddInvalidCar()
{
	CarStore store = createCarStore();
	int errorCode = addCar(&store, -23, "Skoda", "suv");
	assert(errorCode == 0);

	errorCode = addCar(&store, 23, "", "suv");
	assert(errorCode == 0);

	errorCode = addCar(&store, 213, "v", "acasa");
	assert(errorCode == 0);

	MyList* filtered = getAllCars(&store, NULL);
	assert(size(filtered) == 0);
	destroyList(filtered);

	destroyStore(&store);
}

void testSorts() {
	CarStore store = createCarStore();
	addCar(&store, 100, "Audi", "sport");
	addCar(&store, 200, "Skoda", "altele");
	addCar(&store, 500, "MiniCooper", "mini");
	MyList* l = sortByModel(&store);
	Car* p = get(l, 1);
	assert(strcmp(p->model,"MiniCooper") == 0);
	destroyList(l);
	l = sortByCategories(&store);
	p = get(l, 0);
	assert(strcmp(p->categorie, "altele") == 0);
	p = get(l, 1);
	assert(strcmp(p->categorie, "mini") == 0);
	destroyList(l);
	destroyStore(&store);
}

void testUndo() {
	CarStore store = createCarStore();
	addCar(&store, 100, "Audi", "sport");
	addCar(&store, 200, "Skoda", "altele");
	undo(&store);
	MyList* l = getAllCars(&store, NULL);
	assert(size(l) == 1);
	destroyList(l);

	undo(&store);
	l = getAllCars(&store, NULL);
	assert(size(l) == 0);
	destroyList(l);

	assert(undo(&store) != 0);
	assert(undo(&store) != 0);
	assert(undo(&store) != 0);

	destroyStore(&store);
}

void testModify()
{
	CarStore store = createCarStore();
	addCar(&store, 100, "Audi", "suv");
	addCar(&store, 200, "Skoda", "altele");
	modifyCar(&store, 0, "Polo", "suv");
	MyList* l = getAllCars(&store, NULL);
	Car* p = get(l, 0);
	assert(strcmp(p->model, "Polo") == 0);
	destroyList(l);
	destroyStore(&store);
}

void testInchiriat() 
{
	CarStore store = createCarStore();
	addCar(&store, 100, "Audi", "suv");
	addCar(&store, 200, "Skoda", "altele");
	assert(changeInchiriereCar(&store, 0, 1) == 2);
	assert(changeInchiriereCar(&store, 0, 0) == 1);
	destroyStore(&store);
}