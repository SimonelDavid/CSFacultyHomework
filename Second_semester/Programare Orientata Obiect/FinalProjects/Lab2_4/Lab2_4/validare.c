#define _CRT_SECURE_NO_DEPRECATE
#include "domain.h"
#include <string.h>
#include <stdlib.h>

char* validateOferta(Oferta* cheltuialaDeValidat) {

	char* errors = malloc(300);
	if (errors == NULL)
		return NULL;

	strcpy(errors, "");

	if (cheltuialaDeValidat->pret < 0) {
		strcat(errors, "EXCEPTION: Pretul nu poate fi negativ!\n");
	}

	char tip1[5] = "mare";
	char tip2[6] = "munte";
	char tip3[11] = "city break";
	int tipValid = 0;

	if (strcmp(cheltuialaDeValidat->tip, tip1) == 0)
		tipValid = 1;
	if (strcmp(cheltuialaDeValidat->tip, tip2) == 0)
		tipValid = 1;
	if (strcmp(cheltuialaDeValidat->tip, tip3) == 0)
		tipValid = 1;

	if (tipValid == 0) {
		strcat(errors, "EXCEPTION: Tipul cheltuielii trebuie sa fie mare, munte sau city break!\n");
	}
	return errors;
}