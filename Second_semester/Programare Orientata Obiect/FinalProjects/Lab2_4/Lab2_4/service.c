#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "repo.h"
#include "validare.h"

Service* createService(int repositorySize) {
	Service* newService = (Service*)malloc(sizeof(Service));
	if (newService == NULL)
		return NULL;
	newService->repository = createRepository(repositorySize);
	return newService;
}

void deleteService(Service* service, DeleteMethod deleteMethod) {
	deleteRepository(service->repository, deleteMethod);
	free(service);
}


char* serviceAdaugaOferta(Service* service, int data, int pret, char* tip) {
	Oferta* cheltuialaDeAdaugat = createOferta(data, pret, tip);


	char* errors = validateOferta(cheltuialaDeAdaugat);

	if (strcmp(errors, "") == 0) {
		int done = repositoryAdauga(service->repository, cheltuialaDeAdaugat, checkEqualOferte);
		if (done == 0) {
			//Nu s-a adaugat

			strcat(errors, "EXCEPTION: Oferta exista deja!\n");
		}
	}

	if (strcmp(errors, "") != 0) deleteOferta(cheltuialaDeAdaugat);
	return errors;
}

char* serviceModificaOferta(Service* service, int data, int pret, char* tip) {

	Oferta* ofertaNoua = createOferta(data, pret, tip);


	char* errors = validateOferta(ofertaNoua);
	if (strcmp(errors, "") == 0) {
		//Oferta noua e valida
		if (repositoryModifica(service->repository, ofertaNoua) == 0) {
			strcat(errors, "EXCEPTION: ID-ul nu exista!\n");
		}
	}
	else {
		deleteOferta(ofertaNoua);
	}

	return errors;

}

char* serviceStergeOferta(Service* service, int data) {
	char* errors = malloc(100);
	strcpy(errors, "");
	if (repositorySterge(service->repository, data, deleteOfertaRepository) == 0) {
		strcat(errors, "EXCEPTION: ID-ul nu exista!\n");
	}
	return errors;
}


Repository* serviceGetRepositoryFilteredBySuma(Service* service, int pret) {
	Repository* filteredBySuma = createRepository(service->repository->length);


	for (int i = 0; i < service->repository->length; i++) {
		Oferta* cheltuialaCurenta = service->repository->elements[i];
		if (cheltuialaCurenta->pret == pret) {
			repositoryAdauga(filteredBySuma, copyOferta(cheltuialaCurenta), checkEqualOferte);
		}
	}

	return filteredBySuma;
}


Repository* serviceGetRepositoryFilteredByTip(Service* service, char* tip) {
	Repository* filteredByTip = createRepository(service->repository->length);

	for (int i = 0; i < service->repository->length; i++) {
		Oferta* cheltuialaCurenta = service->repository->elements[i];
		if (strcmp(cheltuialaCurenta->tip, tip) == 0) {
			repositoryAdauga(filteredByTip, copyOferta(cheltuialaCurenta), checkEqualOferte);
		}
	}

	return filteredByTip;
}

Repository* serviceGetRepositorySpecialFilter(Service* service, int modulo) {
	Repository* specialFilter = createRepository(service->repository->length);

	for (int i = 0; i < service->repository->length; i++) {
		Oferta* cheltuialaCurenta = service->repository->elements[i];
		if (cheltuialaCurenta->pret % modulo == 0) {
			repositoryAdauga(specialFilter, copyOferta(cheltuialaCurenta), checkEqualOferte);
		}
	}

	return specialFilter;
}


Repository* serviceGetRepositorySortedBySuma(Repository* repository, int reverse) {
	Repository* sortedBySuma = copyRepository(repository, copyOferta);

	int isSorted = 0;
	while (!isSorted) {
		isSorted = 1;
		for (int i = 0; i < sortedBySuma->length - 1; i++) {
			Oferta* c1 = sortedBySuma->elements[i];
			Oferta* c2 = sortedBySuma->elements[i + 1];
			if (c1->pret > c2->pret) {
				isSorted = 0;
				Oferta* aux = sortedBySuma->elements[i];
				sortedBySuma->elements[i] = sortedBySuma->elements[i + 1];
				sortedBySuma->elements[i + 1] = aux;

			}
		}
	}

	if (reverse == 1) {
		for (int i = 0; i < sortedBySuma->length / 2; i++) {
			Oferta* auxiliar = sortedBySuma->elements[i];
			sortedBySuma->elements[i] = sortedBySuma->elements[sortedBySuma->length - 1 - i];
			sortedBySuma->elements[sortedBySuma->length - 1 - i] = auxiliar;
		}
	}

	return sortedBySuma;
}


Repository* serviceGetRepositorySortedByTip(Repository* repository, int reverse) {
	Repository* sortedByTip = copyRepository(repository, copyOferta);

	int isSorted = 0;
	while (!isSorted) {
		isSorted = 1;
		for (int i = 0; i < sortedByTip->length - 1; i++) {
			Oferta* c1 = sortedByTip->elements[i];
			Oferta* c2 = sortedByTip->elements[i + 1];
			if (strcmp(c1->tip, c2->tip) > 0) {
				isSorted = 0;
				Oferta* aux = sortedByTip->elements[i];
				sortedByTip->elements[i] = sortedByTip->elements[i + 1];
				sortedByTip->elements[i + 1] = aux;
			}
		}
	}

	if (reverse == 1) {
		for (int i = 0; i < sortedByTip->length / 2; i++) {
			Oferta* auxiliar = sortedByTip->elements[i];
			sortedByTip->elements[i] = sortedByTip->elements[sortedByTip->length - 1 - i];
			sortedByTip->elements[sortedByTip->length - 1 - i] = auxiliar;
		}
	}

	return sortedByTip;
}



Repository* sortBySumWithFunction(Repository* repository, Comparator comparator) {
	Repository* sortedRepository = copyRepository(repository, copyOferta);

	int isSorted = 0;
	while (!isSorted) {
		isSorted = 1;
		for (int i = 0; i < sortedRepository->length - 1; i++)
			if (comparator(sortedRepository->elements[i], sortedRepository->elements[i + 1]) > 0) {
				Oferta* auxiliar = sortedRepository->elements[i];
				sortedRepository->elements[i] = sortedRepository->elements[i + 1];
				sortedRepository->elements[i + 1] = auxiliar;
				isSorted = 0;
			}
	}
	return sortedRepository;
}

void updateHistory(Repository* historyList, Repository* currentList) {
	repositoryAdauga(historyList, copyRepository(currentList, copyOferta), compareLists);
}


Repository* undoHistory(Repository* history, Repository* currentList) {
	if (history->length == 0) return NULL;
	deleteRepository(currentList, deleteOferta);
	Repository* lastRecord = copyRepository(history->elements[history->length - 1], copyOferta);
	deleteRepository(history->elements[history->length - 1], deleteOferta);
	history->length--;
	return lastRecord;
}