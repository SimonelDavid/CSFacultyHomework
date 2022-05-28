
#ifndef REPO_H_
#define REPO_H_
#include <stdlib.h>
#include "domain.h"

typedef void* ElemType;

typedef void(*DeleteMethod)(ElemType);

typedef int(*DeleteElementMethod)(ElemType, int);

typedef void* (*CopyMethod)(ElemType);

typedef int(*EqualityMethod)(ElemType, ElemType);

typedef  struct {
	int length;
	int capacity;
	ElemType* elements;
}Repository;


//Done
Repository* createRepository(int size);


//Done
void resizeRepository(Repository* repository);


//Done
void deleteRepository(Repository* repositoryToDelete, DeleteMethod deleteMethod);


//Done
Repository* copyRepository(Repository* repository, CopyMethod copyMethod);


//Done
int repositoryAdauga(Repository* repository, void* obiectNou, EqualityMethod equals);

//Done
int repositoryModifica(Repository* repository, void* obiect);

//Sterge o oferta existenta sau returneaza un mesaj daca aceasta nu exista
int repositorySterge(Repository* repository, int id, DeleteElementMethod conditie);


//Functionalitati
void deleteList(Repository*);

void* copyList(Repository* repositoryDeCopiat);

int compareLists(Repository* r1, Repository* r2);

int deleteOfertaRepository(Repository* repository, int id);

int deleteUndoRepository(Repository* repository, int format);

#endif // !REPO_H_