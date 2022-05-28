#include "CarService.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "my_sort.h"
/*
Add a car to the carstore
*/
int addCar(CarStore* store, int numar_inmatriculare, char* model, char* categorie) 
{
	Car masina = createCar(numar_inmatriculare,model,categorie);
	int errorCode = validare_masina(masina);
	if (errorCode == 0) 
	{
		destroyCar(&masina);
		return errorCode;
	}
	add(&store->allCars, masina);
	return 1; // all ok
}

/*
Filter pets in the store
typeSubstring - cstring
return all pets where typeSubstring is a substring of the type
*/

MyList getAllCars(CarStore* store)
{
	return copyList(&store->allCars);
}
/*MyList getAllCars(CarStore* store, char* typeSubstring)
{
	if (typeSubstring == NULL || strlen(typeSubstring) == 0)
		return copyList(&store->allPets);
	
	MyList rez = createEmpty();
	for (int i = 0; i < size(&store->allCars); i++) 
	{
		Car masina = get(&store->allCars, i);
		if (strstr(p.type, typeSubstring) != NULL) {
			add(&rez, copyPet(&p));
		}
	}
	return rez;
}
*/

int modifyCar(CarStore* store, int numar_inmatriculare, char* modelnou, char* categorienoua)
{
	// gasesc elem de inloc
	int index = find_nrinmat(&(store->allCars), numar_inmatriculare);
	if (index == -1) return 0;
	Car elem = get(&(store->allCars), index);
	set_model(&elem, modelnou);
	set_categorie(&elem, categorienoua);
	set(&(store->allCars), index, elem); // store[i] = elem;
	return 1; // cod ok
}

int changeInchiriereCar(CarStore* store, int numar_inmatriculare)
{
	int index = find_nrinmat(&store->allCars, numar_inmatriculare);
	if (index == -1) return 0;
	Car elem = get(&store->allCars, index);
	set_inchiriata(&elem, !elem.inchiriata);
	set(&store->allCars, index, elem);
	return 1+!elem.inchiriata;
}

int cmpModel(Car* masina1, Car* masina2) 
{
	return strcmp(masina1->model, masina2->model);
}

int cmpCategorie(Car* masina1, Car* masina2) 
{
	return strcmp(masina2->categorie, masina1->categorie);
}

/*
 Sort ascending by model
*/
MyList sortByModel(CarStore* store) 
{
	MyList l = copyList(&store->allCars);
	sort(&l, cmpModel);
	return l;
}

/*
Sort ascending by species
*/
MyList sortByCategories(CarStore* store) 
{
	MyList l = copyList(&store->allCars);
	sort(&l, cmpCategorie);
	return l;
}

CarStore createCarStore()
{
	CarStore rez;
	rez.allCars = createEmpty();
	return rez;
}

void destroyStore(CarStore* store)
{
	destroy(&store->allCars);
}

void testAddCar() 
{
	CarStore store = createCarStore();
	addCar(&store, 100,"Skoda","suv");
	addCar(&store, 300,"Audi","altele");
	MyList filtered = getAllCars(&store);
	assert(size(&filtered) == 2);
	destroy(&filtered);

	destroyStore(&store);
}

void testModifyCar() {
	CarStore store = createCarStore();
	addCar(&store, 100, "Skoda", "suv");
	addCar(&store, 300, "Audi", "altele");
	assert(modifyCar(&store, 100, "Ferrari", "sport") == 1);
	assert(modifyCar(&store, 140, "Ferrari", "sport") == 0);
	destroyStore(&store);
}

void testAddInvalidCar() 
{
	CarStore store = createCarStore();
	int errorCode = addCar(&store, -23,"Skoda","suv");
	assert(errorCode == 0);

	errorCode = addCar(&store, 23, "", "suv");
	assert(errorCode == 0);

	errorCode = addCar(&store, 213, "v", "acasa");
	assert(errorCode == 0);

	MyList filtered = getAllCars(&store);
	assert(size(&filtered) == 0);
	destroy(&filtered);

	destroyStore(&store);
}

void testSorts() 
{
	CarStore store = createCarStore();
	addCar(&store, 100,"Skoda","suv");
	addCar(&store, 200,"Audi","altele");
	addCar(&store, 300,"BMW","suv");
	MyList l = sortByModel(&store);
	assert(strcmp(get(&l, 1).model, "BMW") == 0);
	destroy(&l);
	l = sortByCategories(&store);
	assert(strcmp(get(&l, 0).categorie, "suv") == 0);
	assert(strcmp(get(&l, 1).categorie, "suv") == 0);
	destroy(&l);
	destroyStore(&store);
}