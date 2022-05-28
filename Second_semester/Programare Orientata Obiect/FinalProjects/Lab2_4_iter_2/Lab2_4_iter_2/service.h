#pragma once

#include "MyList.h"

typedef struct {
	MyList allOferte;
} StoreOferte;

/*
  create a petstore
*/
StoreOferte createOfertaStore();

void destroyStore(StoreOferte* store);
/*
Add a pet to the store
*/
int addOferta(StoreOferte* store, char* tip, char* destinatie, char* data, int pret);

/*
  Filter pets in the store
  typeSubstring - cstring
  return all pets where typeSubstring is a substring of the tip
*/
MyList getAllOferte(StoreOferte* store, char* typeSubstring);

/*
Sort ascending by tip
*/
MyList sortByTip(StoreOferte* store);

/*
Sort ascending by destinatie
*/
MyList sortByDestinatie(StoreOferte* store);

int modificaOferta(MyList* my_list, int poz, Oferta oferta);

int stergeOferta(MyList* my_list, int id);

void testAddOferta();
void testModificaOferta();
void testStergereOferta();
void testAddInvalidPet();
void testSorts();