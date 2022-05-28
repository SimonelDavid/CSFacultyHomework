#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "consola.h"
#include "repo.h"
#include "service.h"
#include "teste.h"

int main() {

	runAllTests();
	/*
	Service* service = createService(1);
	runConsole(service);
	deleteService(service, deleteOferta);
	_CrtDumpMemoryLeaks();
	*/
}


/*
7. Administrator imobil

Creati o aplicatie care petmite gestiunea de cheltuieli lunare pentru apartamentele dintr - un bloc.

Fiecare oferta are : numarul apartamentului, pret, tipul(mare, munte, city break, mare).

Aplicatia permite :

a) Adaugarea de cheltuieli pentru un apartament

b) Modificarea unei cheltuieli existente(tipul, pret)

c) Stergere oferta

d) Vizualizare lista de cheltuieli filtrat dupa o proprietate(pret, tipul, apartament)

e) Vizualizare lista de cheltuieli ordonat dupa pret sau tip(crescator / descrescator)
*/