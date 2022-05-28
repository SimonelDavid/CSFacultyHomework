#include "MyList.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
/*
Create an empty list
*/
MyList createEmpty() {
	MyList rez;
	rez.lg = 0;
	rez.cap = 2;
	rez.elems = malloc(sizeof(ElemType) * rez.cap);
	return rez;
}

/*
Destroy list
*/
void destroy(MyList* l) {
	//dealocate oferte
	for (int i = 0; i < l->lg; i++) {
		destroyOferta(&l->elems[i]);
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
ElemType set(MyList* l, int poz, Oferta p) {
	ElemType rez = l->elems[poz];
	l->elems[poz] = p;
	return rez;
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
	ElemType* nElems = calloc(l->cap+2, sizeof(ElemType) * newCapacity);
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
void add(MyList* l, ElemType el) {
	ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}

void deleteOferta(MyList* my_list, int id) {

	for (int i = id; i < my_list->lg-1; i++)
	{
		destroyOferta(&my_list->elems[i]);
		my_list->elems[i] = copyOferta(&my_list->elems[i + 1]);
	}
	destroyOferta(&my_list->elems[my_list->lg - 1]);
	my_list->lg--;
}

/*
Make a shallow copy of the list
return Mylist containing the same elements as l
*/
MyList copyList(MyList* l) {
	MyList rez = createEmpty();
	for (int i = 0; i < size(l); i++) {
		ElemType p = get(l, i);
		add(&rez, copyOferta(&p));
	}
	return rez;
}

void testCreateList() {
	MyList l = createEmpty();
	assert(size(&l) == 0);
	destroy(&l);
}
void testIterateList() {
	MyList l = createEmpty();
	add(&l, createOferta("munte", "straja", "10/01/2022", 1000));
	add(&l, createOferta("mare", "mamaia", "10/08/2022", 2000));
	assert(size(&l) == 2);
	Oferta p = get(&l, 0);

	assert(strcmp(p.tip, "munte") == 0);
	p = get(&l, 1);
	assert(strcmp(p.destinatie, "mamaia") == 0);
	destroy(&l);
	assert(size(&l) == 0);
}

void testCopyList() {
	MyList l = createEmpty();
	add(&l, createOferta("munte", "straja", "10/01/2022", 1000));
	add(&l, createOferta("mare", "mamaia", "10/08/2022", 2000));
	MyList l2 = copyList(&l);
	assert(size(&l2) == 2);
	Oferta p = get(&l2, 0);
	assert(strcmp(p.tip, "munte") == 0);
	destroy(&l);
	destroy(&l2);
}

void testResize() {
	MyList l = createEmpty();
	for (int i = 0; i < 10; i++) {
		add(&l, createOferta("munte", "straja", "10/01/2022", 1000));
	}
	assert(size(&l) == 10);
	destroy(&l);
	assert(size(&l) == 0);
	assert(l.elems == NULL);
}
