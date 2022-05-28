#include "CarsRepository.h"
#include "Car.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*
Create an empty list
*/
MyList createEmpty() 
{
	MyList masini;
	masini.lg = 0;
	masini.cap = 2;
	masini.elems = malloc(sizeof(ElemType) * masini.cap);
	return masini;
}

/*
Destroy list
*/
void destroy(MyList* l) 
{
	//dealocate cars
	for (int i = 0; i < l->lg; i++) {
		destroyCar(&l->elems[i]);
	}
	free(l->elems);
	//make harder to miss-use after destroy
	l->elems = NULL;
	l->lg = 0;
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
ElemType set(MyList* l, int poz, Car masina) 
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
		if (elem.numar_inmatriculare == nrinmat)
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
	int newCapacity = l->cap + 2;
	ElemType* nElems = malloc(sizeof(ElemType) * newCapacity);
	//copy elems
	for (int i = 0; i < l->lg; i++) {
		nElems[i] = l->elems[i];
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
		if (el.numar_inmatriculare == masina_din_lista.numar_inmatriculare)
		{
			ElemType* ptr_elem = &(l->elems[i]);
			//set_nr_inmatriculare(ptr_elem, el_nou.numar_inmatriculare);
			set_model(ptr_elem, el_nou.model);
			set_categorie(ptr_elem, el_nou.categorie);
			return;
		}
	}
}


/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
MyList copyList(MyList* l) {
	MyList rez = createEmpty();
	for (int i = 0; i < size(l); i++) {
		ElemType masina = get(l, i);
		add(&rez, copyCar(&masina));
	}
	return rez;
}

void testCreateList() 
{
	MyList l = createEmpty();
	assert(size(&l) == 0);
	destroy(&l);
}

void testIterateList() 
{
	MyList l = createEmpty();
	add(&l, createCar(100,"Audi","suv"));
	add(&l, createCar(200,"Skoda","altele"));
	assert(size(&l) == 2);
	Car masina = get(&l, 0);

	assert(masina.numar_inmatriculare == 100);
	masina = get(&l, 1);
	assert(strcmp(masina.model, "Skoda") == 0);
	destroy(&l);
	assert(size(&l) == 0);
}

void testCopyList() 
{
	MyList l = createEmpty();
	add(&l, createCar(100, "Audi", "suv"));
	add(&l, createCar(200, "Skoda", "altele"));
	MyList l2 = copyList(&l);
	assert(size(&l2) == 2);
	Car masina = get(&l2, 0);
	assert(strcmp(masina.model,"Audi") == 0);
	destroy(&l);
	destroy(&l2);
}

void testResize() 
{
	MyList l = createEmpty();
	for (int i = 0; i < 10; i++) {
		add(&l, createCar(100, "Audi", "suv"));
	}
	assert(size(&l) == 10);
	destroy(&l);
	assert(size(&l) == 0);
	assert(l.elems == NULL);
}

void testFind() {
	MyList l = createEmpty();
	add(&l, createCar(100, "Audi", "suv"));
	add(&l, createCar(200, "Skoda", "altele"));
	assert(find_nrinmat(&l, 100) == 0);
	assert(find_nrinmat(&l, 201) == -1);
	destroy(&l);
}

void testModify()
{
	MyList l = createEmpty();
	add(&l, createCar(100, "Audi", "suv"));
	add(&l, createCar(200, "Skoda", "altele"));
	modify(&l, createCar(100, "Audi", "suv"), createCar(500, "Polo", "suv"));
	assert(strcmp(get(&l, 0).model, "Polo") == 0);
}
