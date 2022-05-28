#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "consola.h"

void printHelpMenu() {
	printf("\n");
	printf("ADMINISTRATOR IMOBIL\n");
	printf("0. Exit application\n");
	printf("1. Adauga oferta\n");
	printf("2. Modifica oferta\n");
	printf("3. Sterge oferta\n");
	printf("4. Filtreaza cheltuieli\n");
	printf("5. Ordoneaza cheltuieli\n");
	printf("6. Afiseaza cheltuielile\n");
	printf("7. Undo\n");
	printf(">>");
}


void uiAfiseazaCheltuieli(Service* service) {
	Repository* repo = service->repository;
	printf("\nLista Cheltuieli:\n");
	for (int i = 0; i < service->repository->length; i++) {
		printf("%d. ", i + 1);
		printOferta(repo->elements[i]);
	}
}

void uiAdaugaCheltuiala(Service* service, Repository* history) {
	int data, pret;
	char tip[11];

	Repository* copyRepoCurent = copyRepository(service->repository, copyOferta);

	int succesCitire = 1;
	printf("Introduceti detaliile pentru o noua oferta:\n");
	printf("data >");
	succesCitire *= scanf("%d", &data);
	printf("pret >");
	succesCitire *= scanf("%d", &pret);
	printf("tip >");
	succesCitire *= scanf("%s", tip);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		deleteRepository(copyRepoCurent, deleteOferta);
		return;
	}

	char* errors = serviceAdaugaOferta(service, data, pret, tip);

	if (strcmp(errors, "") == 0) {
		updateHistory(history, copyRepoCurent);
		printf("Oferta a fost adaugata cu succes!\n");
	}
	else {
		printf("%s", errors);
	}
	deleteRepository(copyRepoCurent, deleteOferta);
	free(errors);
}

void uiModificaCheltuiala(Service* service, Repository* history) {
	int data;
	int sumaNoua;
	char tipNou[21];


	int succesCitire = 1;
	printf("Introduceti id-ul cheltuielii pe care doriti sa o modificati:\n");
	printf("data >");
	succesCitire *= scanf("%d", &data);
	printf("Introduceti noua pret >");
	succesCitire *= scanf("%d", &sumaNoua);
	printf("Introduceti noul tip >");
	succesCitire *= scanf("%s", tipNou);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}
	Repository* copyRepoCurent = copyRepository(service->repository, copyOferta);
	char* errors = serviceModificaOferta(service, data, sumaNoua, tipNou);
	if (strcmp(errors, "") == 0)
	{
		updateHistory(history, copyRepoCurent);
		printf("Oferta a fost modificata cu succes!\n");
	}
	else {
		printf("%s", errors);
	}
	free(errors);
	deleteRepository(copyRepoCurent, deleteOferta);
}

void uiStergeCheltuiala(Service* service, Repository* history) {

	int data, succesCitire = 1;

	printf("Introduceti detaliile cheltuielii pe care doriti sa o stergeti:\n");
	printf("data >");
	succesCitire *= scanf("%d", &data);


	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}
	Repository* copyRepoCurent = copyRepository(service->repository, copyOferta);
	char* errors = serviceStergeOferta(service, data);
	if (strcmp(errors, "") == 0) {
		updateHistory(history, copyRepoCurent);
		printf("Oferta stearsa cu succes!\n");
	}
	else {
		printf("%s", errors);
	}
	free(errors);
	deleteRepository(copyRepoCurent, deleteOferta);
}


void uiFiltreazaCheltuieli(Service* service) {
	printf("Introduceti dupa ce criteriu doriti sa filtrati:\n");
	int option;
	printf("1.Suma\n2.Tip\n3.Special\n>");
	if (scanf("%d", &option) == 0)
		return;

	if (option == 1) {
		printf("Introduceti pret dupa care doriti sa filtrati:\n");
		int pret;
		if (scanf("%d", &pret) == 0)
			return;

		Repository* filteredBySuma = serviceGetRepositoryFilteredBySuma(service, pret);

		if (filteredBySuma->length <= 0)
			printf("Lista filtrata este vida!\n");
		else
		{
			printf("Rezultat:\n");
			for (int i = 0; i < filteredBySuma->length; i++) {
				printOferta(filteredBySuma->elements[i]);
			}
			printf("\n");
		}

		deleteRepository(filteredBySuma, deleteOferta);
	}
	else if (option == 2) {
		printf("Introduceti tipul dupa care doriti sa filtrati (mare/mare/munte/city break):\n");
		char tip[20];
		if (scanf("%s", tip) == 0)
			return;

		Repository* filteredByTip = serviceGetRepositoryFilteredByTip(service, tip);

		if (filteredByTip->length <= 0)
			printf("Lista filtrata este vida!\n");
		else
		{
			printf("Rezultat:\n");
			for (int i = 0; i < filteredByTip->length; i++) {
				printOferta(filteredByTip->elements[i]);
			}
			printf("\n");
		}

		deleteRepository(filteredByTip, deleteOferta);
	}
	else if (option == 3) {
		printf("Introduceti modulo:\n");
		int modulo;
		if (scanf("%d", &modulo) == 0) return;
		Repository* filteredByModulo = serviceGetRepositorySpecialFilter(service, modulo);

		if (filteredByModulo->length <= 0)
			printf("Lista filtrata este vida!\n");
		else
		{
			printf("Rezultat:\n");
			for (int i = 0; i < filteredByModulo->length; i++) {
				printOferta(filteredByModulo->elements[i]);
			}
			printf("\n");
		}

		deleteRepository(filteredByModulo, deleteOferta);

	}
	else {
		printf("EXCEPTION: Invalid option!\n");
	}

}

void uiOrdoneazaCheltuieli(Service* service) {
	printf("Introduceti proprietatea dupa care doriti sa sortati:\n1.Suma\n2.Tip");
	int proprietate;
	if (!scanf("%d", &proprietate))
		return;

	if (proprietate != 1 && proprietate != 2) {
		printf("EXCEPTION: Invalid input!\n");
		return;
	}

	printf("Cum doriti sa sortati:\n1.Crescator\n2.Descrescator\n");
	int sortDirection;
	if (!scanf("%d", &sortDirection))
		return;

	if (sortDirection != 1 && sortDirection != 2) {
		printf("EXCEPTION: Invalid input!\n");
		return;
	}

	int reverse = 0;
	if (sortDirection == 2)
		reverse = 1;

	if (proprietate == 1) {
		Repository* sortedBySuma = serviceGetRepositorySortedBySuma(service->repository, reverse);
		if (sortedBySuma->length <= 0)
			printf("Repository-ul este vid!");
		else
		{
			printf("Rezultat:\n");
			for (int i = 0; i < sortedBySuma->length; i++) {
				printOferta(sortedBySuma->elements[i]);
			}
			printf("\n");
		}

		deleteRepository(sortedBySuma, deleteOferta);
	}
	else if (proprietate == 2) {
		Repository* sortedByTip = serviceGetRepositorySortedByTip(service->repository, reverse); if (sortedByTip->length <= 0)
			printf("Repository-ul este vid!");
		else
		{
			printf("Rezultat:\n");
			for (int i = 0; i < sortedByTip->length; i++) {
				printOferta(sortedByTip->elements[i]);
			}
			printf("\n");
		}

		deleteRepository(sortedByTip, deleteOferta);
	}
}

void printRepository(Repository* repository) {
	for (int i = 0; i < repository->length; i++)
		printOferta(repository->elements[i]);
}


void uiUndoList(Service* service, Repository* undoList) {
	if (undoList->length == 0) {
		printf("Nu se poate realiza Undo!\n");
	}
	else {
		service->repository = undoHistory(undoList, service->repository);
		printf("Undo realizat cu succes!\n");
	}
}

void runConsole(Service* service) {
	const char CODE_EXIT = '0';
	const char CODE_ADD = '1';
	const char CODE_MODIFY = '2';
	const char CODE_DELETE = '3';
	const char CODE_FILTER = '4';
	const char CODE_SORT = '5';
	const char CODE_PRINT = '6';
	const char CODE_UNDO = '7';
	char command;

	Repository* undoList = createRepository(1);

	while (1) {
		printHelpMenu();

		if (scanf(" %c", &command) == 0)
			break;

		if (command == CODE_EXIT) {
			deleteRepository(undoList, deleteList);
			break;
		}
		else if (command == CODE_ADD) {
			uiAdaugaCheltuiala(service, undoList);
		}
		else if (command == CODE_MODIFY) {
			uiModificaCheltuiala(service, undoList);
		}
		else if (command == CODE_DELETE) {
			uiStergeCheltuiala(service, undoList);
		}
		else if (command == CODE_FILTER) {
			uiFiltreazaCheltuieli(service);
		}
		else if (command == CODE_SORT) {
			uiOrdoneazaCheltuieli(service);
		}
		else if (command == CODE_PRINT) {
			uiAfiseazaCheltuieli(service);
		}
		else if (command == CODE_UNDO) {
			uiUndoList(service, undoList);
		}
		else {
			printf("Unknown command");
		}
	}
}
