//begin - added to activate memory leak detection
#define _CRT_SECURE_NO_DEPRECATE
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
//end - added to activate memory leak detection

#include "Car.h"
#include "CarsRepository.h"
#include "CarService.h"
#include <stdio.h>

void testAll() 
{
	testare_CreeazaDistruge_masina();
	testare_validare_masina();
	testCreateList();
	testIterateList();
	testCopyList();
	testFind();
	testModify();
	testAddCar();
	_CrtDumpMemoryLeaks();
/*	testModifyCar();
	testchangeInchiriereCar();
	testAddInvalidCar();
	testResize();
	testSorts();
	testListeDeListe();
	*/
}

/*
  Read car from standard input and add to car store
*/
void ui_addCar(CarStore* store) 
{

	int numar_inmatriculare;
	char* model;
	char* categorie;

	int succesCitire = 1;

	model = (char*)malloc(50 * sizeof(char));
	categorie = (char*)malloc(20 * sizeof(char));
	printf("%s", "Numarul de inmatriculare: ");
	succesCitire *= scanf("%d", &numar_inmatriculare);


	printf("%s", "Modelul masinii: ");
	succesCitire *= scanf("%s", model);


	printf("%s", "Categoria masinii: ");
	succesCitire *= scanf("%s", categorie);
	printf("\n");

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	int error = addCar(store, numar_inmatriculare, model, categorie);
	if (error == 0)
		printf("Invalid car!\n");
	else
		printf("Masina adaugata cu succes!\n");

	free(model);
	free(categorie);

}

void actualizareCars(CarStore* store)
{
	int numar_inmatriculare;
	char* model;
	char* categorie;

	int succesCitire = 1;

	model = (char*)malloc(50 * sizeof(char));
	categorie = (char*)malloc(20 * sizeof(char));
	printf("%s", "Numarul de inmatriculare al masinii: ");
	succesCitire *= scanf("%d", &numar_inmatriculare);


	printf("%s", "Modelul nou al masinii: ");
	succesCitire *= scanf("%s", model);


	printf("%s", "Categoria noua a masinii: ");
	succesCitire *= scanf("%s", categorie);
	printf("\n");


	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	int error = modifyCar(store, numar_inmatriculare, model, categorie);
	if (error == 0)
	{
		printf("Eroare!\n");
	}
	else {
		printf("Succes!\n");
	}
}

void printAllCars(MyList* l) 
{
	printf("Cars:\n");
	for (int i = 0; i < size(l); i++) 
	{
		Car* masina = get(l, i);
		printf("Numar inmatriculare: %d, Model: %s, Categorie: %s\n", masina->numar_inmatriculare, masina->model, masina->categorie);
	}
}


void showAll(CarStore* store) 
{
	MyList* allCars = getAllCars(store);
	printAllCars(&allCars);
	destroy(&allCars, destroyCar);
}

void sortBModel(CarStore* store) 
{
	MyList* allCars = sortByModel(store);
	printAllCars(&allCars);
	destroy(&allCars, destroyCar);
}

void sortBCategories(CarStore* store) 
{
	MyList* allCars = sortByCategories(store);
	printAllCars(&allCars);
	destroy(&allCars, destroyCar);
}

void inchiriereCars(CarStore* store)
{
	int numar_inmatriculare;
	int succesCitire = 1;
	printf("%s", "Numarul de inmatriculare al masinii: ");
	succesCitire *= scanf("%d", &numar_inmatriculare);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	int error = changeInchiriereCar(store, numar_inmatriculare);
	if (error == 0)
	{
		printf("NU am putut gasi aceasta masina!\n");
	}
	else {
		printf("%s %s.\n", "Aceasta masina este acum", (error-1==0)?("returnata"):("inchiriata"));
	}
}

void filterModel(CarStore* store)
{
	char* model;

	int succesCitire = 1;

	model = (char*)malloc(50 * sizeof(char));
	printf("%s", "Modelul nou al masinii: ");
	succesCitire *= scanf("%s", model);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	MyList* cars = &(store->allCars);
	MyList* output = createEmpty();
	for (int i = 0; i < size(cars); ++i)
	{
		Car* elem = get(cars, i);
		if (strcmp(elem->model, model) == 0)
			add(&output, elem);
	}
	printAllCars(&output);
}

void filterCategorie(CarStore* store)
{
	char* categorie;

	int succesCitire = 1;

	categorie = (char*)malloc(20 * sizeof(char));
	printf("%s", "Categoria noua a masinii: ");
	succesCitire *= scanf("%s", categorie);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	MyList* cars = &(store->allCars);
	MyList* output = createEmpty();
	for (int i = 0; i < size(cars); ++i)
	{
		Car* elem = get(cars, i);
		if (strcmp(elem->categorie, categorie) == 0)
			add(&output, elem);
	}
	printAllCars(&output);
}


void run() 
{
	CarStore store = createCarStore();
	int ruleaza = 1;
	while (ruleaza) 
	{
		printf("1 Add\n2 Update\n3 All\n4 Sort by type\n5 Sort by categories\n6 Inchiriaza\n7 Filtrare dupa categorie\n8 Filtrare dupa model\n0 Exit\nCommand:");
		int cmd = 0;
		int succesCitire = 1;
		succesCitire *= scanf("%d", &cmd);
		switch (cmd) 
		{
		case 1:
			ui_addCar(&store);
			break;
		case 2:
			actualizareCars(&store);
			break;
		case 3:
			showAll(&store);
			break;
		case 4:
			sortBModel(&store);
			break;
		case 5:
			sortBCategories(&store);
			break;
		case 6:
			inchiriereCars(&store);
			break;
		case 8: 
			filterModel(&store);
			break;
		case 7:
			filterCategorie(&store);
			break;
		case 0:
			ruleaza = 0;
			break;
		default:
			printf("Comanda invalida!!!\n");
		}
		if (succesCitire == 0) {
			printf("EXCEPTION: Comanda invalida!\n");
			return;
		}
	}
	destroyStore(&store);
}

int main() 
{
	testAll();
	//comment out run() when running OpenCPPCoverage
	//run();
	//print memory leak
	return 0;
}


