#include "CarRepository.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
/*
Create an empty list
*/
MyList* createEmpty(DestroyFct f) {
	MyList* masina = malloc(sizeof(MyList));
	if (masina != NULL) {
		masina->lg = 0;
		masina->cap = 2;
		masina->elems = malloc(sizeof(ElemType) * masina->cap);
		masina->dfnc = f;
	}
	return masina;
}

/*
Destroy list
*/
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
ElemType set(MyList* l, int poz, ElemType p) {
	ElemType masina= l->elems[poz];
	l->elems[poz] = p;
	return masina;
}

/*
return number of elements in the list
*/
int size(MyList* l) {
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
	int newCapacity = l->cap + 2;
	ElemType* nElems = calloc(l->cap + 2, sizeof(ElemType) * newCapacity);
	//copy elems
	if (nElems != NULL) {
		for (int i = 0; i < l->lg; i++) {
			nElems[i] = l->elems[i];
		}
	}
	//dealocate old vector
	free(l->elems);
	l->elems = nElems;
	l->cap += 2;
}
/*
Add element into the list
post: element is added to the end of the list
*/
void add(MyList* l, ElemType el) {
	ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}

/*
Remove last element from the list
!!!! do not destroy removed element
return the removed element
*/
ElemType removeLast(MyList* l) {
	ElemType masina = l->elems[l->lg - 1];
	l->lg -= 1;	
	return masina;
}

/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
MyList* copyList(MyList* l,CopyFct cf) {
	MyList* masina = createEmpty(l->dfnc);
	for (int i = 0; i < size(l); i++) {
		ElemType p = get(l, i);		
		add(masina, cf(p));
	}
	return masina;
}

void testCreateList() {
	MyList* l = createEmpty(destroyCar);
	assert(size(l) == 0);
	destroyList(l);
}
void testIterateList() {
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100, "Audi", "suv"));
	add(l, createCar(200, "Skoda", "altele"));
	assert(size(l) == 2);
	Car* p = get(l,0);

	assert(strcmp(p->model,"Audi") == 0);
	p = get(l, 1);
	assert(strcmp(p->categorie, "altele") == 0);
	destroyList(l);
}

void testCopyList() {
	MyList* l = createEmpty(destroyCar);
	add(l, createCar(100, "Audi", "suv"));
	add(l, createCar(200, "Skoda", "altele"));
	MyList* l2 = copyList(l,copyCar);
	assert(size(l2) == 2);
	Car* p = get(l2, 0);
	assert(strcmp(p->model, "Audi") == 0);
	destroyList(l);
	destroyList(l2);
}

void testResize() {
	MyList* l = createEmpty(destroyCar);
	for (int i = 0; i < 10; i++) {
		add(l, createCar(100, "Audi", "suv"));
	}
	assert(size(l) == 10);
	destroyList(l);	
}


void testListOfLists() {
	MyList* listOfLists = createEmpty(destroyList);
	MyList* listOfCars = createEmpty(destroyCar);
	add(listOfCars, createCar(100, "Audi", "suv"));
	add(listOfCars, createCar(200, "Skoda", "altele"));
	add(listOfCars, createCar(500, "Polo", "suv"));
	add(listOfLists, listOfCars);
	MyList* cpy = copyList(listOfCars, copyCar);
	add(listOfLists, cpy);
	assert(size(listOfLists) == 2);
	assert(size(listOfCars) == 3);

	MyList* el2 = get(listOfLists, 1);
	assert(size(el2) == 3);

	destroyList(listOfLists);
}

/*
  create and initialize an int on the heap
*/
int* createIntOnHeap(int value) {
	int* pi = malloc(sizeof(int));
	if (pi != NULL) {
		*pi = value;
	}
	return pi;
}
void testListOfInts() {	
	MyList* l = createEmpty(free);//use stdlib free to free memory
	
	add(l, createIntOnHeap(0));
	add(l, createIntOnHeap(1));
	add(l, createIntOnHeap(2));
	add(l, createIntOnHeap(3));
	add(l, createIntOnHeap(4));
	add(l, createIntOnHeap(0));
	assert(size(l) == 6);

	int* nr = get(l, 3);
	assert(*nr == 3);

	destroyList(l);
}

void testRemoveLast() {
	MyList* listOfCars = createEmpty(destroyCar);
	add(listOfCars, createCar(500, "Polo", "suv"));
	add(listOfCars, createCar(500, "Polo", "suv"));
	assert(size(listOfCars) == 2);
	Car* el = removeLast(listOfCars);
	assert(size(listOfCars) == 1);
	destroyCar(el);

	el = removeLast(listOfCars);
	assert(size(listOfCars) == 0);
	destroyCar(el);

	destroyList(listOfCars);
}