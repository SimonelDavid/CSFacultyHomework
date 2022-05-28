#define _CRT_SECURE_NO_DEPRECATE
#include "domain.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



Oferta* createOferta(int data, int pret, char* tip) {
	Oferta* ofertaNoua = malloc(sizeof(Oferta));
	ofertaNoua->data = data;
	ofertaNoua->pret = pret;
	strcpy(ofertaNoua->tip, tip);

	return ofertaNoua;
}

Oferta* copyOferta(Oferta* oferta) {
	return createOferta(oferta->data, oferta->pret, oferta->tip);
}

void deleteOferta(Oferta* oferta) {
	free(oferta);
}


int checkEqualOferte(Oferta* oferta1, Oferta* oferta2) {
	return oferta1->data == oferta2->data;
}

void printOferta(Oferta* oferta) {
	printf("Apartament nr=%d, pret=%d, tip=%s \n", oferta->data, oferta->pret, oferta->tip);
}