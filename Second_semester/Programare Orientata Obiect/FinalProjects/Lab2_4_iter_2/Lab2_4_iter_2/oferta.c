#define _CRT_SECURE_NO_DEPRECATE
#include "oferta.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
/*
Create a new pet
*/
Oferta createOferta(char* tip, char* destinatie, char* data, int pret) {
	Oferta rez;

	size_t nrC = strlen(tip) + 1;
	rez.tip = malloc(sizeof(char) * nrC);
	if (rez.tip != NULL) {
		strcpy(rez.tip, tip);
	}

	nrC = strlen(destinatie) + 1;
	rez.destinatie = malloc(sizeof(char) * nrC);
	if (rez.destinatie != NULL) {
		strcpy(rez.destinatie, destinatie);
	}

	nrC = strlen(data) + 1;
	rez.data = malloc(sizeof(char) * nrC);
	if (rez.data != NULL) {
		strcpy(rez.data, data);
	}

	rez.pret = pret;
	return rez;
}

/*
Dealocate memory occupied by pet
*/
void destroyOferta(Oferta* p) {
	free(p->tip);
	free(p->destinatie);
	free(p->data);
	//mark that oferta is destroyed, avoid accidental use after destroy
	//helps in debug
	p->data = NULL;
	p->tip = NULL;
	p->destinatie = NULL;
	p->pret = -1;
}
/*
  Create a copy for the pet
  Deep copy - copy all the sub-parts
*/
Oferta copyOferta(Oferta* p) {
	return createOferta(p->tip, p->destinatie, p->data, p->pret);
}

int validate(Oferta p) {
	if (strlen(p.destinatie) == 0) {
		return 1;
	}

	if (strlen(p.tip) == 0) {
		return 2;
	}
	char tip1[5] = "mare";
	char tip2[6] = "munte";
	char tip3[11] = "city_break";
	if ((strcmp(p.tip, tip1) != 0) && (strcmp(p.tip, tip2) != 0) && (strcmp(p.tip, tip3) != 0)) {
		return 2;
	}

	if (p.pret < 0) {
		return 3;
	}

	return 0;
}


void testCreateDestroy() {
	Oferta p = createOferta("munte", "straja", "20/12/2021", 1000);
	assert(strcmp(p.tip, "munte") == 0);
	assert(strcmp(p.destinatie, "straja") == 0);
	assert(strcmp(p.data, "20/12/2021") == 0);
	assert(p.pret == 1000.0);

	destroyOferta(&p);
	assert(p.tip == NULL);
	assert(p.destinatie == NULL);
	assert(p.pret == -1);
}