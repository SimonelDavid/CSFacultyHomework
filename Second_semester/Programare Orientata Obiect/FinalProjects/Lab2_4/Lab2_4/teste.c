#define _CRT_SECURE_NO_DEPRECATE
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "domain.h"
#include "validare.h"
#include "service.h"
#include "repo.h"

void testCreateCheltuiala() {
	Oferta* ofertaNoua = createOferta(10022022, 200, "mare");
	assert(ofertaNoua->data == 10022022);
	assert(ofertaNoua->pret == 200);
	assert(strcmp(ofertaNoua->tip, "mare") == 0);
	free(ofertaNoua);
}

void testValidateCheltuiala() {
	char* errors;
	Oferta* cheltuialaDeValidat = createOferta("10/02/2022", 200, "mare");
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "") == 0);
	free(errors);

	strcpy(cheltuialaDeValidat->tip, "munte");
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "") == 0);
	free(errors);

	strcpy(cheltuialaDeValidat->tip, "city break");
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "") == 0);
	free(errors);

	cheltuialaDeValidat->data = "10/02/2022";
	cheltuialaDeValidat->pret = -100;
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "EXCEPTION: Pretul nu poate fi negativ!\n") == 0);
	free(errors);

	cheltuialaDeValidat->pret = 200;
	strcpy(cheltuialaDeValidat->tip, "curent");
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "EXCEPTION: Tipul cheltuielii trebuie sa fie mare, munte sau city break!\n") == 0);
	free(errors);

	cheltuialaDeValidat->pret = -2;
	errors = validateOferta(cheltuialaDeValidat);
	assert(strcmp(errors, "EXCEPTION: Pretul nu poate fi negativ!\nEXCEPTION: Tipul cheltuielii trebuie sa fie mare, munte sau city break!\n") == 0);
	free(errors);

	deleteOferta(cheltuialaDeValidat);
}


void testCreateAndDeleteRepository() {
	Repository* repository = createRepository(5);
	assert(repository->capacity == 5);
	deleteRepository(repository, deleteList);
}

void testAdaugaRepository() {
	Repository* repository = createRepository(1);
	Repository* undo1 = createRepository(4);
	Oferta* c1 = createOferta(14, 100, "mare");
	Oferta* c2 = createOferta(15, 100, "mare");
	Oferta* c3 = createOferta(16, 100, "mare");
	Oferta* c4 = createOferta(17, 100, "mare");
	Oferta* c5 = createOferta(17, 100, "mare");
	assert(repositoryAdauga(undo1, c1, checkEqualOferte) == 1);
	assert(repositoryAdauga(undo1, c2, checkEqualOferte) == 1);
	assert(repositoryAdauga(undo1, c3, checkEqualOferte) == 1);
	assert(repositoryAdauga(undo1, c4, checkEqualOferte) == 1);
	assert(repositoryAdauga(undo1, c5, checkEqualOferte) == 0);
	free(c5);
	assert(repositoryAdauga(repository, undo1, compareLists) == 1);
	assert(undo1->length == 4);
	assert(repository->length == 1);
	deleteRepository(repository, deleteList);

}

void testCopyRepository() {
	Repository* repoBoss = createRepository(1);
	Repository* undo1 = createRepository(1);
	repositoryAdauga(undo1, createOferta(14, 100, "mare"), checkEqualOferte);
	repositoryAdauga(undo1, createOferta(15, 100, "mare"), checkEqualOferte);
	repositoryAdauga(undo1, createOferta(16, 100, "mare"), checkEqualOferte);
	repositoryAdauga(undo1, createOferta(17, 100, "mare"), checkEqualOferte);
	repositoryAdauga(repoBoss, undo1, compareLists);
	Oferta* cheltuialaInvalida = createOferta(14, 150, "mare");
	assert(repositoryAdauga(undo1, cheltuialaInvalida, checkEqualOferte) == 0);
	free(cheltuialaInvalida);
	Repository* undoCopy = copyRepository(undo1, copyOferta);
	Repository* repoBossCopy = copyRepository(repoBoss, copyList);
	assert(undoCopy->length == undo1->length);
	assert(repoBoss->length == repoBossCopy->length);
	Repository* aux1 = repoBoss->elements[0];
	Repository* aux2 = repoBossCopy->elements[0];
	assert(aux1->length == aux2->length);

	Oferta* c1 = aux1->elements[0];
	Oferta* c2 = aux2->elements[0];
	assert(c2->pret == c1->pret);

	c2->pret++;

	assert(c1->pret != c2->pret);

	deleteRepository(repoBoss, deleteList);
	deleteRepository(repoBossCopy, deleteList);
	deleteRepository(undoCopy, deleteOferta);
}

void testResizeRepository() {
	Repository* repository = createRepository(1);
	assert(repository->length == 0);
	assert(repository->capacity == 1);
	repositoryAdauga(repository, createOferta(10, 100, "mare"), checkEqualOferte);
	repositoryAdauga(repository, createOferta(12, 100, "mare"), checkEqualOferte);
	assert(repository->length == 2);
	assert(repository->capacity == 2);
	repositoryAdauga(repository, createOferta(13, 100, "mare"), checkEqualOferte);
	assert(repository->length == 3);
	assert(repository->capacity == 4);
	deleteRepository(repository, deleteOferta);
}

void testModificaRepository() {
	//Se aplica doar listelor de cheltuieli, nu si listelor de liste
	Repository* repository = createRepository(1);

	Oferta* c1 = createOferta(1, 10, "mare");
	Oferta* c2 = createOferta(2, 20, "mare");

	repositoryAdauga(repository, c1, checkEqualOferte);
	repositoryAdauga(repository, c2, checkEqualOferte);

	Oferta* c2Mod = createOferta(2, 30, "city break");
	Oferta* cNegasit = createOferta(3, 100, "--");

	assert(repositoryModifica(repository, c2Mod) == 1);
	assert(repositoryModifica(repository, cNegasit) == 0);

	Oferta* cTest = repository->elements[1];
	assert(cTest->pret == 30);

	deleteRepository(repository, deleteOferta);
}

void testStergeRepository() {

	Repository* repository = createRepository(1);
	Oferta* c1 = createOferta(1, 1, "mare");
	Oferta* c2 = createOferta(2, 1, "mare");
	Oferta* c3 = createOferta(3, 1, "mare");
	assert(repositoryAdauga(repository, c1, checkEqualOferte) == 1);
	assert(repositoryAdauga(repository, c2, checkEqualOferte) == 1);
	assert(repositoryAdauga(repository, c3, checkEqualOferte) == 1);

	assert(repositorySterge(repository, 2, deleteOfertaRepository) == 1);
	assert(repository->length == 2);

	deleteRepository(repository, deleteOferta);

	Repository* repoBoss = createRepository(1);
	Repository* undo1 = createRepository(1);
	Repository* undo2 = createRepository(1);

	repositoryAdauga(undo1, createOferta(1, 1, "mare"), checkEqualOferte);

	Repository* copieUndo1 = copyRepository(undo1, copyOferta);
	Repository* copieUndo2 = copyRepository(undo2, copyOferta);

	assert(repositoryAdauga(repoBoss, undo1, compareLists) == 1);
	assert(repositoryAdauga(repoBoss, undo2, compareLists) == 1);

	assert(repositorySterge(repoBoss, 0, deleteUndoRepository) == 1);

	Repository* copieRepoBoss = copyRepository(repoBoss, copyList);

	deleteRepository(repoBoss, deleteList);

	assert(copieUndo1->length == 1);
	assert(copieRepoBoss->length == 1);

	deleteRepository(copieUndo1, deleteOferta);
	deleteRepository(copieUndo2, deleteOferta);
	deleteRepository(copieRepoBoss, deleteList);

}


void testAdaugaCheltuialaService() {
	Service* service = createService(3);
	assert(service->repository->length == 0);
	assert(service->repository->capacity == 3);
	char* errors;

	errors = serviceAdaugaOferta(service, 1, 1, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 1);

	errors = serviceAdaugaOferta(service, 1, -10, "curent");
	assert(strcmp(errors, "EXCEPTION: Pretul nu poate fi negativ!\nEXCEPTION: Tipul cheltuielii trebuie sa fie mare, munte sau city break!\n") == 0);
	free(errors);
	assert(service->repository->length == 1);

	Oferta* oferta = service->repository->elements[0];
	assert(oferta->data == 1);
	assert(oferta->pret == 1);
	assert(strcmp(oferta->tip, "mare") == 0);


	errors = serviceAdaugaOferta(service, 1, 1, "mare");
	assert(strcmp(errors, "EXCEPTION: Oferta exista deja!\n") == 0);
	free(errors);
	assert(service->repository->length == 1);

	errors = serviceAdaugaOferta(service, 10032022, 1, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 2);
	assert(service->repository->capacity == 3);


	errors = serviceAdaugaOferta(service, 10042022, 1, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 3);
	assert(service->repository->capacity == 3);

	deleteService(service, deleteOferta);
}



void testModificaCheltuialaService() {


	Service* service = createService(3);
	assert(service->repository->length == 0);
	assert(service->repository->capacity == 3);
	char* errors;

	errors = serviceAdaugaOferta(service, 1, 1, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 1);

	errors = serviceAdaugaOferta(service, 2, 2, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 2);

	errors = serviceAdaugaOferta(service, 3, 3, "city break");
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 3);

	errors = serviceModificaOferta(service, 10, 1, "mare");
	assert(strcmp(errors, "EXCEPTION: ID-ul nu exista!\n") == 0);
	free(errors);
	Oferta* oferta1 = service->repository->elements[0];
	assert(oferta1->data == 10 && oferta1->pret == 1 && strcmp(oferta1->tip, "mare") == 0);


	errors = serviceModificaOferta(service, 2, 200, "munte");
	assert(strcmp(errors, "") == 0);
	free(errors);
	Oferta* oferta2 = service->repository->elements[1];
	assert(oferta2->data == 10032022 && oferta2->pret == 200 && strcmp(oferta2->tip, "munte") == 0);

	errors = serviceModificaOferta(service, 3, 300, "curent");
	assert(strcmp(errors, "EXCEPTION: Tipul cheltuielii trebuie sa fie mare, munte, city break sau mare!\n") == 0);
	free(errors);
	Oferta* cheltuiala3 = service->repository->elements[2];
	assert(cheltuiala3->data == 10042022 && cheltuiala3->pret == 3 && strcmp(cheltuiala3->tip, "city break") == 0);

	deleteService(service, deleteOferta);
}


void testStergeCheltuialaService() {

	Service* service = createService(1);

	char* errors = serviceAdaugaOferta(service, 1, 10, "mare");
	assert(strcmp(errors, "") == 0);
	free(errors);

	errors = serviceAdaugaOferta(service, 2, 20, "mare");
	free(errors);

	errors = serviceAdaugaOferta(service, 3, 30, "mare");
	free(errors);

	assert(service->repository->length == 3);

	errors = serviceStergeOferta(service, 2);
	assert(strcmp(errors, "") == 0);
	free(errors);
	assert(service->repository->length == 2);

	errors = serviceStergeOferta(service, 4);
	assert(strcmp(errors, "EXCEPTION: ID-ul nu exista!\n") == 0);
	free(errors);

	deleteService(service, deleteOferta);
}

void testFilterBySum() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 1, "mare"));
	free(serviceAdaugaOferta(service, 2, 1, "mare"));
	free(serviceAdaugaOferta(service, 3, 2, "mare"));

	assert(service->repository->length == 3);

	Repository* repoFiltered = serviceGetRepositoryFilteredBySuma(service, 1);
	assert(repoFiltered->length == 2);

	Repository* repoFiltered2 = serviceGetRepositoryFilteredBySuma(service, 5);
	assert(repoFiltered2->length == 0);

	deleteRepository(repoFiltered, deleteOferta);
	deleteRepository(repoFiltered2, deleteOferta);
	deleteService(service, deleteOferta);
}

void testFilterByTip() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 1, "mare"));
	free(serviceAdaugaOferta(service, 2, 1, "mare"));
	free(serviceAdaugaOferta(service, 3, 2, "munte"));

	assert(service->repository->length == 3);

	Repository* filteredRepo = serviceGetRepositoryFilteredByTip(service, "mare");
	Repository* filteredRepo2 = serviceGetRepositoryFilteredByTip(service, "inv");

	assert(filteredRepo->length == 2);
	assert(filteredRepo2->length == 0);

	deleteRepository(filteredRepo, deleteOferta);
	deleteRepository(filteredRepo2, deleteOferta);
	deleteService(service, deleteOferta);
}

void specialFilter() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 14, "mare"));
	free(serviceAdaugaOferta(service, 2, 15, "mare"));
	free(serviceAdaugaOferta(service, 3, 21, "munte"));

	assert(service->repository->length == 3);

	Repository* filteredBy7 = serviceGetRepositorySpecialFilter(service, 7);
	Repository* filteredBy4 = serviceGetRepositorySpecialFilter(service, 4);

	assert(filteredBy7->length == 2);
	assert(filteredBy4->length == 0);

	deleteRepository(filteredBy7, deleteOferta);
	deleteRepository(filteredBy4, deleteOferta);
	deleteService(service, deleteOferta);
}

void testSortareBySuma() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 10, "mare"));
	free(serviceAdaugaOferta(service, 2, 20, "mare"));
	free(serviceAdaugaOferta(service, 3, 50, "munte"));
	free(serviceAdaugaOferta(service, 4, 40, "mare"));
	free(serviceAdaugaOferta(service, 5, 60, "munte"));
	free(serviceAdaugaOferta(service, 6, 80, "mare"));

	Repository* repoSortat = serviceGetRepositorySortedBySuma(service->repository, 0);

	assert(repoSortat->length == 6);
	Oferta* c0 = repoSortat->elements[0];
	Oferta* c1 = repoSortat->elements[1];
	Oferta* c2 = repoSortat->elements[2];
	Oferta* c3 = repoSortat->elements[3];
	Oferta* c4 = repoSortat->elements[4];
	Oferta* c5 = repoSortat->elements[5];

	assert(c0->pret == 10);
	assert(c1->pret == 20);
	assert(c2->pret == 40);
	assert(c3->pret == 50);
	assert(c4->pret == 60);
	assert(c5->pret == 80);

	Repository* repoSortatReverse = serviceGetRepositorySortedBySuma(service->repository, 1);

	assert(repoSortat->length == 6);
	Oferta* c0r = repoSortatReverse->elements[0];
	Oferta* c1r = repoSortatReverse->elements[1];
	Oferta* c2r = repoSortatReverse->elements[2];
	Oferta* c3r = repoSortatReverse->elements[3];
	Oferta* c4r = repoSortatReverse->elements[4];
	Oferta* c5r = repoSortatReverse->elements[5];

	assert(c0r->pret == 80);
	assert(c1r->pret == 60);
	assert(c2r->pret == 50);
	assert(c3r->pret == 40);
	assert(c4r->pret == 20);
	assert(c5r->pret == 10);

	deleteRepository(repoSortatReverse, deleteOferta);
	deleteRepository(repoSortat, deleteOferta);
	deleteService(service, deleteOferta);

}

void testSortareByTip() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 10, "mare"));
	free(serviceAdaugaOferta(service, 2, 20, "mare"));
	free(serviceAdaugaOferta(service, 3, 50, "munte"));
	free(serviceAdaugaOferta(service, 4, 40, "mare"));
	free(serviceAdaugaOferta(service, 5, 60, "munte"));
	free(serviceAdaugaOferta(service, 6, 80, "mare"));

	Repository* repoSortat = serviceGetRepositorySortedByTip(service->repository, 0);

	assert(repoSortat->length == 6);
	Oferta* c0 = repoSortat->elements[0];
	Oferta* c1 = repoSortat->elements[1];
	Oferta* c2 = repoSortat->elements[2];
	Oferta* c3 = repoSortat->elements[3];
	Oferta* c4 = repoSortat->elements[4];
	Oferta* c5 = repoSortat->elements[5];

	assert(strcmp(c0->tip, "mare") == 0);
	assert(strcmp(c1->tip, "mare") == 0);
	assert(strcmp(c2->tip, "mare") == 0);
	assert(strcmp(c3->tip, "mare") == 0);
	assert(strcmp(c4->tip, "munte") == 0);
	assert(strcmp(c5->tip, "munte") == 0);

	Repository* repoSortatrev = serviceGetRepositorySortedByTip(service->repository, 1);

	Oferta* c0r = repoSortatrev->elements[0];
	Oferta* c1r = repoSortatrev->elements[1];
	Oferta* c2r = repoSortatrev->elements[2];
	Oferta* c3r = repoSortatrev->elements[3];
	Oferta* c4r = repoSortatrev->elements[4];
	Oferta* c5r = repoSortatrev->elements[5];

	assert(strcmp(c0r->tip, "munte") == 0);
	assert(strcmp(c1r->tip, "munte") == 0);
	assert(strcmp(c2r->tip, "mare") == 0);
	assert(strcmp(c3r->tip, "mare") == 0);
	assert(strcmp(c4r->tip, "mare") == 0);
	assert(strcmp(c5r->tip, "mare") == 0);

	deleteRepository(repoSortatrev, deleteOferta);
	deleteRepository(repoSortat, deleteOferta);
	deleteService(service, deleteOferta);
}

int compareCheltuieliSuma(Oferta* oferta1, Oferta* oferta2) {
	return oferta1->pret - oferta2->pret;
}

void testSortareWithComparator() {
	Service* service = createService(1);
	free(serviceAdaugaOferta(service, 1, 10, "mare"));
	free(serviceAdaugaOferta(service, 2, 20, "mare"));
	free(serviceAdaugaOferta(service, 3, 50, "munte"));
	free(serviceAdaugaOferta(service, 4, 40, "mare"));
	free(serviceAdaugaOferta(service, 5, 60, "munte"));
	free(serviceAdaugaOferta(service, 6, 80, "mare"));

	Repository* repoSortat = sortBySumWithFunction(service->repository, compareCheltuieliSuma);

	assert(repoSortat->length == 6);
	Oferta* c0 = repoSortat->elements[0];
	Oferta* c1 = repoSortat->elements[1];
	Oferta* c2 = repoSortat->elements[2];
	Oferta* c3 = repoSortat->elements[3];
	Oferta* c4 = repoSortat->elements[4];
	Oferta* c5 = repoSortat->elements[5];

	assert(c0->pret == 10);
	assert(c1->pret == 20);
	assert(c2->pret == 40);
	assert(c3->pret == 50);
	assert(c4->pret == 60);
	assert(c5->pret == 80);

	deleteRepository(repoSortat, deleteOferta);
	deleteService(service, deleteOferta);
}

void testUndo() {
	Service* service = createService(1);
	Repository* undoList = createRepository(1);

	updateHistory(undoList, service->repository);
	free(serviceAdaugaOferta(service, 1, 1, "mare"));

	updateHistory(undoList, service->repository);
	free(serviceAdaugaOferta(service, 2, 1, "mare"));

	updateHistory(undoList, service->repository);
	free(serviceAdaugaOferta(service, 3, 1, "mare"));

	assert(service->repository->length == 3);
	assert(undoList->length == 3);

	service->repository = undoHistory(undoList, service->repository);
	assert(service->repository->length == 2);
	assert(undoList->length == 2);

	service->repository = undoHistory(undoList, service->repository);
	assert(service->repository->length == 1);
	assert(undoList->length == 1);

	service->repository = undoHistory(undoList, service->repository);
	assert(service->repository->length == 0);
	assert(undoList->length == 0);

	deleteService(service, deleteOferta);
	deleteRepository(undoList, deleteList);

}

void runAllTests() {
	assert(1);
	testCreateCheltuiala();
	testValidateCheltuiala();
	testCreateAndDeleteRepository();
	testAdaugaRepository();
	testCopyRepository();
	testModificaRepository();
	testStergeRepository();
	testResizeRepository();
	testAdaugaCheltuialaService();
	testModificaCheltuialaService();
	testStergeCheltuialaService();
	testFilterBySum();
	testFilterByTip();
	specialFilter();
	testSortareBySuma();
	testSortareByTip();
	testSortareWithComparator();
	testUndo();

	printf("Tests passed! yaaa\n");
}
