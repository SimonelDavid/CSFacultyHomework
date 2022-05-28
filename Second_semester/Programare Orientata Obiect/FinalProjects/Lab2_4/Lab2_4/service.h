#ifndef SERVICE_H_
#define SERVICE_H_

#include "repo.h"
typedef struct {
	Repository* repository;
}Service;

//Creaza un service cu repository-ul de size "repositorySize;
//Done
Service* createService(int repositorySize);

//Elibereaza memoria utilizata de repository
//Done
void deleteService(Service* service, DeleteMethod deleteMethod);

//Permite utilizatorului introducerea datelor pentru o noua oferta
//Done
char* serviceAdaugaOferta(Service* service, int data, int pret, char* tip);

//Modifica o oferta existenta sau returneaza un mesaj daca aceasta nu exista
//Done
char* serviceModificaOferta(Service* service, int data, int pret, char* tip);

//Sterge o oferta existenta si returneaza un cod
//Done
char* serviceStergeOferta(Service* service, int data);

//Returneaza un repository de cheltuieli filtrata dupa pret
//Done
Repository* serviceGetRepositoryFilteredBySuma(Service* service, int pret);

//Returneaza un repository de cheltuieli filtrata dupa tip
//Done
Repository* serviceGetRepositoryFilteredByTip(Service* service, char* tip);

//Done
Repository* serviceGetRepositorySpecialFilter(Service* service, int modulo);

//Returneaza un repository de cheltuieli sortat dupa pret
//Done
Repository* serviceGetRepositorySortedBySuma(Repository* repository, int reverse);

//Returneaza un repository de cheltuieli sortat dupa tip
//Done
Repository* serviceGetRepositorySortedByTip(Repository* repository, int reverse);

//Done
Repository* sortBySumWithFunction(Repository* repository, Comparator comparator);

void updateHistory(Repository* historyList, Repository* currentList);

Repository* undoHistory(Repository* historyList, Repository* currentList);

#endif // !SERVICE_H_