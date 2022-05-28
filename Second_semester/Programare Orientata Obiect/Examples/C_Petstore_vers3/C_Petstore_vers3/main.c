//added for memory leak detection
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <crtdbg.h>

#include "Car.h"
#include "CarRepository.h"
#include "CarService.h"

#include <stdio.h>

void testAll() {
	testCreateDestroy();
	testare_validare_masina();
	testCreateList();
	testIterateList();
	testCopyList();
	testAddCar();
	testAddInvalidCar();
	testResize();
	testSorts();
	testListOfLists();
	testListOfInts();
	testRemoveLast();
	testUndo();
	testModify();
	testInchiriat();
}
/*
  Read car from standard input and add to car store
*/
void readCar(CarStore* store) {
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

	int error = addCar(store, numar_inmatriculare, model, categorie);
	if (error == 0 && succesCitire == 0)
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

	int error = modifyCar(store, numar_inmatriculare, model, categorie);
	if (error == 0 && succesCitire == 0)
	{
		printf("Eroare!\n");
	}
	else {
		printf("Succes!\n");
	}
}

void printAllcars(MyList* l) {
	printf("Cars:\n");
	for (int i = 0; i < size(l); i++) {
		Car* p = get(l, i);
		printf("Nr_Inmat:%d Model:%s Categorie:%s\n", p->numar_inmatriculare, p->model, p->categorie);
	}
}

void filterCars(CarStore* store) {
	printf("Model filter substring:");
	char filterStr[30];
	scanf_s("%s", filterStr, 30);	
	MyList* filteredL = getAllCars(store, filterStr);
	printAllcars(filteredL);
	destroyList(filteredL);
}

void showAll(CarStore* store) {
	MyList* allCars = getAllCars(store, NULL);
	printAllcars(allCars);
	destroyList(allCars);
}

void sortBType(CarStore* store) {
	MyList* allCars = sortByModel(store);
	printAllcars(allCars);
	destroyList(allCars);
}

void inchiriereCars(CarStore* store)
{
	int index;
	int succesCitire = 1;
	printf("%s", "Numarul de inmatriculare al masinii: ");
	succesCitire *= scanf("%d", &index);

	int error = changeInchiriereCar(store, index, 1);
	if (error == 0 && succesCitire == 0)
	{
		printf("NU am putut gasi aceasta masina!\n");
	}
	else {
		printf("%s %s.\n", "Aceasta masina este acum", (error - 1 == 0) ? ("returnata") : ("inchiriata"));
	}
}

void sortBSpec(CarStore* store) {
	MyList* allCars = sortByCategories(store);
	printAllcars(allCars);
	destroyList(allCars);
}

void run() {
	CarStore store = createCarStore();
	int ruleaza = 1;
	while (ruleaza) {
		printf("1 Add\n2 Update\n3 Filter\n4 All\n5 Sort by model\n6 Rent a car\n7 Sort by categorie\n8 Undo\n0 Exit\nCommand:");
		int cmd = 0;
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			readCar(&store);
			break;
		case 2:
			actualizareCars(&store);
			break;
		case 3:	
			filterCars(&store);			
			break;
		case 4:
			showAll(&store);
			break;
		case 5:
			sortBType(&store);
			break;
		case 6:
			inchiriereCars(&store);
			break;
		case 7:
			sortBSpec(&store);
			break;
		case 8:
			if (undo(&store) != 0) {
				printf("No more undo!!!\n");
			}
			break;
		case 0:
			ruleaza = 0;		
			break;
		default:
			printf("Comanda invalida!!!\n");
		}
	}
	destroyStore(&store);
}

int main() {
	testAll();
	//run();
	_CrtDumpMemoryLeaks();//print memory leak
	return 0;
}