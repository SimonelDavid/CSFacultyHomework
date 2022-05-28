#include "service.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mysort.h"
/*
Add a pet to the store
*/
int addOferta(StoreOferte* store, char* tip, char* destinatie, char* data, int pret) {
	Oferta p = createOferta(tip, destinatie, data, pret);
	int errorCode = validate(p);
	if (errorCode != 0) {
		destroyOferta(&p);
		return errorCode;
	}
	add(&store->allOferte, p);
	return 0; // all ok
}

/*
Filter pets in the store
typeSubstring - cstring
return all pets where typeSubstring is a substring of the tip
*/
MyList getAllOferte(StoreOferte* store, char* typeSubstring) {
	if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
		return copyList(&store->allOferte);
	}
	MyList rez = createEmpty();
	for (int i = 0; i < size(&store->allOferte); i++) {
		Oferta p = get(&store->allOferte, i);
		if (strstr(p.tip, typeSubstring) != NULL) {
			add(&rez, copyOferta(&p));
		}
	}
	return rez;
}

int cmpType(Oferta* p1, Oferta* p2) {
	return strcmp(p1->tip, p2->tip);
}

int cmpSpe(Oferta* p1, Oferta* p2) {
	return strcmp(p1->destinatie, p2->destinatie);
}

/*
 Sort ascending by tip
*/
MyList sortByTip(StoreOferte* store) {
	MyList l = copyList(&store->allOferte);
	sort(&l, cmpType);
	return l;
}

/*
Sort ascending by destinatie
*/
MyList sortByDestinatie(StoreOferte* store) {
	MyList l = copyList(&store->allOferte);
	sort(&l, cmpSpe);
	return l;
}

StoreOferte createOfertaStore()
{
	StoreOferte rez;
	rez.allOferte = createEmpty();
	return rez;
}

void destroyStore(StoreOferte* store)
{
	destroy(&store->allOferte);
}

int modificaOferta(MyList* my_list, int poz, Oferta oferta) {
	if (poz > my_list->lg)
		return 0;
	else {
		set(my_list, poz, oferta);
		return 1;
	}
}

int stergeOferta(MyList* my_list, int id) {
	if (id >= my_list->lg)
		return 0;
	else {
		deleteOferta(my_list, id);
		return 1;
	}
}

void testAddOferta() {
	StoreOferte store = createOfertaStore();
	addOferta(&store, "munte", "straja", "10/01/2022", 1000);
	addOferta(&store, "mare", "mamaia", "10/08/2022", 2000);
	MyList filtered = getAllOferte(&store, NULL);
	assert(size(&filtered) == 2);
	destroy(&filtered);

	filtered = getAllOferte(&store, "mare");
	assert(size(&filtered) == 1);
	destroy(&filtered);

	filtered = getAllOferte(&store, "2");
	assert(size(&filtered) == 0);
	destroy(&filtered);

	filtered = getAllOferte(&store, "a");
	assert(size(&filtered) == 1);
	destroy(&filtered);

	destroyStore(&store);
}

void testModificaOferta() {
	StoreOferte store = createOfertaStore();
	addOferta(&store, "munte", "straja", "10/01/2022", 1000);
	addOferta(&store, "mare", "mamaia", "10/08/2022", 2000);
	MyList my_list = getAllOferte(&store, NULL);

	Oferta p = createOferta("city break", "barcelona", "20/05/2021", 1500);
	
	assert(modificaOferta(&my_list, 0, p) == 1);

	assert(modificaOferta(&my_list, 3, p) == 0);
	destroy(&my_list);
	destroyStore(&store);
}

void testStergereOferta() {
	StoreOferte store = createOfertaStore();
	addOferta(&store, "munte", "straja", "10/01/2022", 1000);
	addOferta(&store, "mare", "mamaia", "10/08/2022", 2000);
	MyList my_list = getAllOferte(&store, NULL);

	assert(stergeOferta(&my_list, 0) == 1);

	assert(stergeOferta(&my_list, 3) == 0);
	destroy(&store);
	destroy(&my_list);
}

void testAddInvalidPet() {
	StoreOferte store = createOfertaStore();
	int errorCode = addOferta(&store, "", "straja", "10/01/2022", 1000);
	assert(errorCode != 0);

	errorCode = addOferta(&store, "munte", "", "10/01/2022", 1000);
	assert(errorCode != 0);

	errorCode = addOferta(&store, "munte", "straja", "10/01/2022", -1000);
	assert(errorCode != 0);

	errorCode = addOferta(&store, "schi", "straja", "10/01/2022", -1000);
	assert(errorCode != 0);

	MyList filtered = getAllOferte(&store, NULL);
	assert(size(&filtered) == 0);
	destroy(&filtered);

	destroyStore(&store);
}

void testSorts() {
	StoreOferte store = createOfertaStore();
	addOferta(&store, "munte", "straja", "10/01/2022", 1000);
	addOferta(&store, "mare", "mamaia", "10/08/2022", 2000);
	addOferta(&store, "city_break", "barcelona", "12/05/2022", 1500);
	MyList l = sortByTip(&store);
	assert(strcmp(get(&l, 1).tip, "mare") == 0);
	destroy(&l);
	l = sortByDestinatie(&store);
	assert(strcmp(get(&l, 0).destinatie, "barcelona") == 0);
	assert(strcmp(get(&l, 1).destinatie, "mamaia") == 0);
	destroy(&l);
	destroyStore(&store);
}