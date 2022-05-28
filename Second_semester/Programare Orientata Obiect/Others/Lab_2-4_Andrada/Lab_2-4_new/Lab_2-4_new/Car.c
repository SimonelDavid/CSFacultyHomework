#include "Car.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*
Create a new Car
*/
Car createCar(int numar_inmatriculare, char* model, char* categorie) 
{
	Car masina;
	masina.numar_inmatriculare = numar_inmatriculare;
	size_t nrC = strlen(model) + 1;
	masina.model = malloc(sizeof(char) * nrC);
	if(masina.model!=NULL)
		strcpy(masina.model, model);
	//strcpy_s(masina.model, nrC, type);
	nrC = strlen(categorie) + 1;
	masina.categorie = malloc(sizeof(char) * nrC);

	if(masina.categorie!=NULL)
		strcpy(masina.categorie, categorie);
	//strcpy_s(rez.species, nrC, species);
	masina.inchiriata = 0;
	return masina;
}

/*
Dealocate memory occupied by car
*/
void destroyCar(Car* masina) 
{
	free(masina->model);
	free(masina->categorie);
	//mark that car is destroyed, avoid accidental use after destroy
	//helps in debug
	masina->numar_inmatriculare = -1;
	masina->model = NULL;
	masina->categorie = NULL;
}

#pragma region setteri


void set_nr_inmatriculare(Car* masina, int nr_inamtriculare)
{
	(*masina).numar_inmatriculare = nr_inamtriculare;
}

void set_model(Car* masina, char* model)
{
	strcpy((*masina).model, model);
}

void set_categorie(Car* masina, char* categorie)
{
	strcpy((*masina).categorie, categorie);
}

void set_inchiriata(Car* masina, int inchiriata)
{
	masina->inchiriata = inchiriata;
}

#pragma endregion

/*
  Create a copy for the car
  Deep copy - copy all the sub-parts
*/
Car copyCar(Car* masina) 
{
	return createCar(masina->numar_inmatriculare, masina->model, masina->categorie);
}


int masini_egale(Car masina1, Car masina2)
{
	if (masina1.numar_inmatriculare == masina2.numar_inmatriculare && strcmp(masina1.model, masina2.model) == 0 && strcmp(masina1.categorie, masina2.categorie) == 0)
		return 1;
	return 0;
}


//----------------------------------------------------

int validare_categorie(char* categorie)
{
	/*char categorii_disponibile[50] = "mini,sport,suv,altele";

	char* p = strtok(categorii_disponibile, ",");
	while (p != NULL)
	{
		if (strcmp(p, categorie) == 0)
		{
			//free(categorii_disponibile);
			return 1;
		}
			
		p = strtok(NULL, ",");
	}
	//free(categorii_disponibile);
	*/
	if (strcmp(categorie, "mini") == 0)
		return 1;

	if (strcmp(categorie, "sport") == 0)
		return 1;

	if (strcmp(categorie, "suv") == 0)
		return 1;

	if (strcmp(categorie, "altele") == 0)
		return 1;

	return 0;
}


int validare_masina(Car masina) 
{

	if (masina.numar_inmatriculare <= 0)
		return 0;

	if (strlen(masina.model) == 0)
		return 0;

	if (validare_categorie(masina.categorie) == 0)
		return 0;

	return 1;

}

//---------------------------------------------------

/*void testCreateDestroy()
{
	Car masina = createCar(300, "Skoda", "suv");
	assert(masina.numar_inmatriculare == 300);
	assert(strcmp(masina.model, "Skoda") == 0);
	assert(strcmp(masina.categorie, "suv") == 0);

	int numar_inmatriculare = 300;
	char* model = "Skoda";
	char* categorie = "suv";
	Car aceeasi_masina = createCar(numar_inmatriculare, model, categorie);
	assert(masini_egale(masina, aceeasi_masina));

	destroyCar(&masina);
	assert(masina.numar_inmatriculare == -1);
	assert(masina.model == NULL);
	assert(masina.categorie == NULL);

}*/

void testare_CreeazaDistruge_masina()
{
	Car masina;
	int numar_inmatriculare = 300;
	char* model = "Skoda";
	char* categorie = "suv";

	masina = createCar(numar_inmatriculare, model, categorie);
	assert(masina.numar_inmatriculare == numar_inmatriculare);
	assert(strcmp(masina.model, model) == 0);
	assert(strcmp(masina.categorie, categorie) == 0);

	Car aceeasi_masina;
	aceeasi_masina = createCar(numar_inmatriculare, model, categorie);
	assert(masini_egale(masina, aceeasi_masina));

	destroyCar(&masina);
	assert(masina.numar_inmatriculare == -1);
	assert(masina.model == NULL);
	assert(masina.categorie == NULL);

}



void testare_validare_masina()
{
	Car masina, masina2, masina3, masina4;

	int numar_inmatriculare = 300;
	char* model = "Skoda";
	char* categorie = "suv";

	masina = createCar(numar_inmatriculare, model, categorie);

	numar_inmatriculare = -23;
	model = "Audi";
	categorie = "altele";

	masina2 = createCar(numar_inmatriculare, model, categorie);

	assert(validare_masina(masina));
	assert(validare_masina(masina2) == 0);


	numar_inmatriculare = 300;
	model = "";
	categorie = "suv";

	masina3 = createCar(numar_inmatriculare, model, categorie);
	assert(validare_masina(masina3) == 0);

	numar_inmatriculare = 400;
	model = "orice";
	categorie = "suvi";

	masina4 = createCar(numar_inmatriculare, model, categorie);
	assert(validare_masina(masina4) == 0);
}



