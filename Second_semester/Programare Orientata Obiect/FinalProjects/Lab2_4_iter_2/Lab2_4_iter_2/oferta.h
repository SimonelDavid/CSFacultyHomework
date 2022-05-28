#pragma once
typedef struct {
	char* tip;
	char* destinatie;
	char* data;
	int pret;
} Oferta;

/*
Create a new pet
*/
Oferta createOferta(char* tip, char* destinatie, char* data, int pret);

/*
 Dealocate memory occupied by pet
*/
void destroyOferta(Oferta* p);

/*
Create a copy for the pet
Deep copy - copy all the sub-parts
*/
Oferta copyOferta(Oferta* p);

/*
   Validate pet
   return !=0 if pet is invalid
*/
int validate(Oferta p);

void testCreateDestroy();

