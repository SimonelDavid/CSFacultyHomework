//begin - added to activate memory leak detection
#define _CRT_SECURE_NO_DEPRECATE
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//end - added to activate memory leak detection

#include "oferta.h"
#include "MyList.h"
#include "service.h"

#include <stdio.h>

void testAll() {
	testCreateDestroy();
	testCreateList();
	testIterateList();
	testCopyList();
	testAddOferta();
	testModificaOferta();
	testStergereOferta();
	testAddInvalidPet();
	testResize();
	testSorts();
}
/*
  Read pet from standard input and add to pet store
*/
void citesteOferta(StoreOferte* store) {
	char tip[31];
	char destinatie[31];
	char data[31];
	int pret;

	int succesCitire = 1;

	printf("Introduceti noul tip: ");
	succesCitire *= scanf("%s", tip);

	printf("Introduceti noua destinatie: ");
	succesCitire *= scanf("%s", destinatie);

	printf("Introduceti noua data: ");
	succesCitire *= scanf("%s", data);

	printf("Introduceti noul pret: ");
	succesCitire *= scanf("%d", &pret);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	int error = addOferta(store, tip, destinatie, data, pret);
	if (error != 0) {
		printf("Oferta Invalida.\n");
	}
	else {
		printf("Oferta adaugata.\n");
	}
}

void printOferte(MyList* l) {
	printf("Oferte:\n");
	for (int i = 0; i < size(l); i++) {
		Oferta p = get(l, i);
		printf("Tip:%s Destinatie:%s Data:%s Pret:%d\n", p.tip, p.destinatie, p.data, p.pret);
	}
}

void filtreazaOferte(StoreOferte* store) {
	printf("Type filter substring:");
	char filterStr[30];
	scanf_s("%s", filterStr, 30);
	MyList filteredL = getAllOferte(store, filterStr);
	printOferte(&filteredL);
	destroy(&filteredL);
}

void showAll(StoreOferte* store) {
	MyList allOferte = getAllOferte(store, NULL);
	printOferte(&allOferte);
	destroy(&allOferte);
}

void sortBType(StoreOferte* store) {
	MyList allOferte = sortByTip(store);
	printOferte(&allOferte);
	destroy(&allOferte);
}

void sortBSpec(StoreOferte* store) {
	MyList allOferte = sortByDestinatie(store);
	printOferte(&allOferte);
	destroy(&allOferte);
}

void ModificaOferta(StoreOferte* store) {
	MyList allOferte = getAllOferte(store, NULL);
	char dataNoua[31];
	int id;
	int pretNou;
	char tipNou[21];
	char destinatieNoua[31];

	int succesCitire = 1;
	printf("Introduceti id-ul ofertei pe care doriti sa o modificati:\n");
	printf("id: ");
	succesCitire *= scanf("%d", &id);

	printf("Introduceti noul tip: ");
	succesCitire *= scanf("%s", tipNou);

	printf("Introduceti noua destinatie: ");
	succesCitire *= scanf("%s", destinatieNoua);

	printf("Introduceti noua data: ");
	succesCitire *= scanf("%s", dataNoua);

	printf("Introduceti noul pret: ");
	succesCitire *= scanf("%d", &pretNou);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}

	Oferta oferta = createOferta(tipNou, destinatieNoua, dataNoua, pretNou);

	int modificare = modificaOferta(&allOferte, id, oferta);

	if (modificare == 1) {
		printf("Modificarea a fost efectuata cu succes!\n");
		printOferte(&allOferte);
	}
	else 
		printf("Modificarea nu a fost efectuata!\n");

	destroy(&allOferte);
}

void StergeOferta(StoreOferte* store) {
	MyList allOferte = getAllOferte(store, NULL);
	int id;

	int succesCitire = 1;
	printf("Introduceti id-ul ofertei pe care doriti sa o stergeti:\n");
	printf("id: ");
	succesCitire *= scanf("%d", &id);

	if (succesCitire == 0) {
		printf("EXCEPTION: Citire invalida!\n");
		return;
	}
	int modificare = stergeOferta(&allOferte, id);

	if (modificare == 1) {
		printf("Modificarea a fost efectuata cu succes!\n");
		printOferte(&allOferte);
	}
	else
		printf("Modificarea nu a fost efectuata!\n");

	destroy(&allOferte);
}

void run() {
	StoreOferte store = createOfertaStore();
	int ruleaza = 1;
	while (ruleaza) {
		printf("1 Adauga Oferta noua\n2 Filtreaza\n3 Afiseaza ofertele\n4 SOrteaza dupa tip\n5 Sorteaza dupa destinatie\n6 Modifica Oferta\n7 Sterge o oferta\n0 Exit\nCommand:");
		int cmd = 0;
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			citesteOferta(&store);
			break;
		case 2:
			filtreazaOferte(&store);
			break;
		case 3:
			showAll(&store);
			break;
		case 4:
			sortBType(&store);
			break;
		case 5:
			sortBSpec(&store);
			break;
		case 6:
			ModificaOferta(&store);
			break;
		case 7:
			StergeOferta(&store);
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
	//comment out run() when running OpenCPPCoverage
	//run();
	_CrtDumpMemoryLeaks();//print memory leak
	return 0;
}