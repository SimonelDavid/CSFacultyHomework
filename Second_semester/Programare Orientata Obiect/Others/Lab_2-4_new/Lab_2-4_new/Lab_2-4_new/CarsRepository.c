#include "CarsRepository.h"
#include "Car.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
Create an empty list
*/
MyList* createEmpty(DestroyFunction f) 
{
	MyList* masini = malloc(sizeof(MyList));
	masini->cap = 2;
	masini->elems = malloc(sizeof(Car) * masini->cap);
	masini->lg = 0;
	masini->dfnc = f;
	return masini;
}

void destroyListaCar(MyList* l) {
	destroy(l, destroyCar);
}

/*
Destroy list
*/
void destroy(MyList* l, DestroyFunction destrF) 
{
	//dealocate cars
	for (int i = 0; i < l->lg; i++) {
		ElemType p = l->elems[i];
		destrF(p);
	}
	free(l->elems);
	free(l);
}

void destroyList(MyList* l) {
	//dealocate pets
	for (int i = 0; i < l->lg; i++) {
		l->dfnc(l->elems[i]);
	}
	free(l->elems);
	free(l);
}

/*
Get an element from the list
poz - position of the element, need to be valid
return element on the given position
*/
ElemType get(MyList* l, int poz) {
	return l->elems[poz];
}

/*
  Modify the element on the given pozition
  return the overwrited element
*/
ElemType set(MyList* l, int poz, Car* masina) 
{
	ElemType car = l->elems[poz];
	l->elems[poz] = masina;
	return car;
}

// cauta elementul in lista
int find_nrinmat(MyList* l, int nrinmat)
{
	for (int i = 0; i < size(l); ++i)
	{
		ElemType elem = get(l, i);
		if (elem->numar_inmatriculare == nrinmat)
		{
			return i; // cod ok
		}
	}
	return -1;
}

/*
return number of elements in the list
*/
int size(MyList* l) 
{
	return l->lg;
}

/*
  Allocate more memory if needed
*/
void ensureCapacity(MyList* l) {
	if (l->lg < l->cap) {
		return; //we have room
	}
	//alocate more memory
	int newCapacity = l->cap * 2;
	ElemType* nElems = malloc(sizeof(ElemType) * newCapacity);
	//copy elems
	if (nElems != NULL) {
		for (int i = 0; i < l->lg; i++) {
			nElems[i] = l->elems[i];
		}
	}
	//dealocate old vector
	free(l->elems);
	l->elems = nElems;
	l->cap = newCapacity;
}
/*
Add element into the list
post: element is added to the end of the list
*/
void add(MyList* l, ElemType el) 
{
	ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}

void modify(MyList* l, ElemType el, ElemType el_nou)
{
	for (int i = 0; i < size(l); i++)
	{
		ElemType masina_din_lista = get(l, i);
		if (el->numar_inmatriculare == masina_din_lista->numar_inmatriculare)
		{
			ElemType* ptr_elem = l->elems[i];
			set_model(ptr_elem, el_nou->model);
			set_categorie(ptr_elem, el_nou->categorie);
			return;}}
}

ElemType removeLast(MyList* l) {
	ElemType rez = l->elems[l->lg - 1];
	l->lg -= 1;
	return rez;
}

/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l, CopyFct cf) {
	MyList* rez = createEmpty(destroyCar);
	for (int i = 0; i < size(l); i++) {
		ElemType masina = get(l, i);
		add(rez, cf(masina));
	}
	return rez;
}

void testCreateList() 
{
	MyList* l = createEmpty(destroyCar);
	assert(size(l) == 0);
	destroy(l, destroyCar);
}

void testIterateList() 
{
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100,"Audi","suv"));
	add(l, createCar(200,"Skoda","altele"));
	assert(size(l) == 2);
	Car* masina = get(l, 0);

	assert(masina->numar_inmatriculare == 100);

	masina = get(l, 1);
	assert(strcmp(masina->model, "Skoda") == 0);
	destroy(l, destroyCar);
}

void testCopyList() 
{
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100, "Audi", "suv"));
	add(l, createCar(200, "Skoda", "altele"));
	MyList* l2 = copyList(l, copyCar);
	assert(size(l2) == 2);
	Car* masina = get(l2, 0);
	assert(strcmp(masina->model,"Audi") == 0);
	destroy(l2, destroyCar);
	destroy(l, destroyCar);
}

void testResize() 
{
	MyList* l = createEmpty(destroyCar);
	for (int i = 0; i < 10; i++) {
		add(l, createCar(100, "Audi", "suv"));
	}
	assert(size(l) == 10);
	destroy(l, destroyCar);
}

void testFind() {
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100, "Audi", "suv"));
	add(l, createCar(200, "Skoda", "altele"));
	assert(find_nrinmat(l, 100) == 0);
	assert(find_nrinmat(l, 201) == -1);
	destroy(l, destroyCar);
}

void testListeDeListe() {
	MyList* myCars = createEmpty(destroyCar);
	add(myCars, createCar(150, "Tiguan", "suv"));
	add(myCars, createCar(150, "Tiguan", "suv"));

	MyList* myCars2 = createEmpty(destroyCar);
	MyList* undoL = createEmpty(destroyCar);
	add(undoL, myCars);
	assert(size(undoL) == 1);
	add(undoL, myCars2);
	assert(size(undoL) == 2);
	
	destroy(undoL, destroyListaCar);
}

void testModify()
{
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100, "Audi", "suv"));
	add(l, createCar(200, "Skoda", "altele"));
	Car* masina = get(l, 0);
	Car* masina1;
	int numar_inmatriculare = 300;
	char* model = "Polo";
	char* categorie = "suv";

	masina1 = createCar(numar_inmatriculare, model, categorie);
	modify(l, masina, masina1);
	assert(strcmp(get(l, 0)->model, "Polo") == 0);
	destroy(l, destroyCar);
	destroyCar(masina1);
}
