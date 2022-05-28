#define _CRT_SECURE_NO_DEPRECATE
#include "repo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Repository* createRepository(int size) {
	Repository* newRepository = (Repository*)malloc(sizeof(Repository));
	if (newRepository == NULL)
		return NULL;

	newRepository->length = 0;
	newRepository->capacity = size;
	newRepository->elements = malloc(newRepository->capacity * sizeof(ElemType));
	return newRepository;
}

void resizeRepository(Repository* repositoryToResize) {

	ElemType* newElements = malloc(repositoryToResize->capacity * 2 * sizeof(ElemType));

	for (int i = 0; i < repositoryToResize->length; i++) {
		newElements[i] = repositoryToResize->elements[i];
	}

	free(repositoryToResize->elements);
	repositoryToResize->elements = newElements;
	repositoryToResize->capacity *= 2;
}

void deleteRepository(Repository* repositoryToDelete, DeleteMethod deleteMethod) {

	for (int i = 0; i < repositoryToDelete->length; i++) deleteMethod(repositoryToDelete->elements[i]);
	free(repositoryToDelete->elements);
	free(repositoryToDelete);

}

Repository* copyRepository(Repository* repository, CopyMethod copyMethod) {
	Repository* newRepository = createRepository(repository->capacity);
	newRepository->length = repository->length;
	for (int i = 0; i < repository->length; i++) {
		newRepository->elements[i] = copyMethod(repository->elements[i]);
	}
	return newRepository;

}

int repositoryAdauga(Repository* repository, void* obiectDeAdaugat, EqualityMethod equals) {
	if (repository->length >= repository->capacity)
		resizeRepository(repository);

	for (int i = 0; i < repository->length; i++) {
		if (equals(repository->elements[i], obiectDeAdaugat)) return 0; //Deja exista
	}

	repository->elements[repository->length++] = obiectDeAdaugat;
	return 1;
}

int repositoryModifica(Repository* repository, Oferta* oferta) {
	const int CODE_SUCCESS = 1;
	const int CODE_NOT_FOUND = 0;

	for (int i = 0; i < repository->length; i++) {
		if (checkEqualOferte(oferta, repository->elements[i])) {
			free(repository->elements[i]);
			repository->elements[i] = oferta;
			return CODE_SUCCESS;
		}
	}
	free(oferta);
	return CODE_NOT_FOUND;

}

int repositorySterge(Repository* repository, int id, DeleteElementMethod deleteMethod) {
	return deleteMethod(repository, id);
}

void deleteList(Repository* repository) {
	deleteRepository(repository, deleteOferta);
}

void* copyList(Repository* repositoryDeCopiat) {
	Repository* newRepo = malloc(sizeof(Repository));
	newRepo->capacity = repositoryDeCopiat->capacity;
	newRepo->length = repositoryDeCopiat->length;
	newRepo->elements = malloc(newRepo->capacity * sizeof(void*));
	for (int i = 0; i < newRepo->length; i++) {
		newRepo->elements[i] = copyOferta(repositoryDeCopiat->elements[i]);
	}
	return newRepo;
}

int compareLists(Repository* r1, Repository* r2) {
	return r1 && r2 && 0;
}

int deleteOfertaRepository(Repository* repository, char id) {
	int i = 0;
	int gasit = 0;
	while (i < repository->length && !gasit) {
		Oferta* cheltuialaCurenta = repository->elements[i];
		if (cheltuialaCurenta->data == id) gasit = 1;
		i++;
	}
	i -= 1;
	if (gasit) {
		for (int j = i; j < repository->length - 1; j++)
		{
			deleteOferta(repository->elements[j]);
			repository->elements[j] = copyOferta(repository->elements[j + 1]);
		}
		deleteOferta(repository->elements[repository->length - 1]);
		repository->length--;
		return 1;
	}
	else {
		return 0;
	}
}

int deleteUndoRepository(Repository* repository, int format) {
	//format nu are nicio valoare. Ajuta la pastrarea formatului pentru functia generica
	format = 0;
	if (repository->length == 0) return 0;
	deleteRepository(repository->elements[repository->length - 1], deleteOferta);
	repository->length--;
	return 1;
}