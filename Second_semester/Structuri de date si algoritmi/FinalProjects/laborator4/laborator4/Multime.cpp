#include "Multime.h"
#include "IteratorMultime.h"
#include "VectorDinamic.h"

#include <iostream>

#define NOVALUE -50000

// Constructor - umple vectorii dinamici cu NULL_VAL
// Complexitate Theta(1) : face 5 pasi
Multime::Multime() {
	prim = -1;
	ultim = -1;

	int i;
	for (i = 0; i < capacitate; i++)
	{
		e.add(NOVALUE);
		urm.add(i + 1);
		prec.add(i - 1);
	}
	// urmator pt. ultimul element este -1
	urm.set(capacitate - 1, -1);

	primLiber = 0;

}

// CAZ FAVORABL : Theta(1) (Vectorii nu trebuie redimensionati
// CAZ NEFAVORABIL : Theta(n) ( n- dimensiunea vectorilor )
// OVERALL : O(n)
int Multime::aloca() {
	//se verifica daca mai este spatiu si daca nu se realoca spatiul liber si se redimensioneaza vectorii
	if (primLiber == -1) {
		resetSpatiuLiber();
	}

	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urm.get(primLiber);
	return i;

}

// Theta(1)
void Multime::dealoca(int i) {
	urm.set(i, primLiber);
	prec.set(i, -1);
	primLiber = i;
}

// Theta(1)
int Multime::creeazaNod(TElem e)
{
	int i = aloca();
	this->e.set(i, e);
	urm.set(i, -1);
	prec.set(i, -1);

	return i;
}

// Theta(n)
void Multime::resetSpatiuLiber()
{
	e.resize();
	urm.resize();
	prec.resize();

	prec.add(-1);
	primLiber = capacitate;
	for (int i = capacitate; i < 2 * capacitate; i++)
	{
		urm.add(i + 1);
		e.add(NOVALUE);
		if (i != capacitate)
			prec.add(i - 1);

	}
	capacitate *= 2;
	urm.set(capacitate - 1, -1);

}

// CAZ FAVORABIL : Theta(1) : cauta gaseste el. pe prima poz
// CAZ NEFAVORABIL : Theta(n) - se face redimensionarea in creeazaNod->aloca->resetSpatiuLiber
// OVERALL : O(n)
bool Multime::adauga(TElem elem) {
	if (cauta(elem))
	{
		// Elementul exista in multime, deci nu va fi adaugat
		return false;
	}
	else
	{
		// Elementul nu exista in multime, deci va fi adaugat
		int i = creeazaNod(elem);
		urm.set(i, prim);
		if (prim != -1)
			prec.set(prim, i);
		prim = i;
		if (dimensiune == 0)
			ultim = i;

		dimensiune++;
		return true;
	}
}

//T(n0 = n(cautare) + n/2(cautare+stergere) =>
// O(n)
bool Multime::sterge(TElem elem) {
	if (!cauta(elem))
		// Elementul nu exista in multime deci nu avem ce sterge
		return false;
	else
	{
		// Elementul exista in multime deci vom efectua stergerea
		int start, end;
		start = prim;
		end = ultim;

		while (end != -1 && start != -1)
		{
			if (elem == e.get(start))
			{

				e.set(start, NOVALUE);

				if (prec.get(start) != -1)
					urm.set(prec.get(start), urm.get(start));

				if (urm.get(start) != -1)
					prec.set(urm.get(start), prec.get(start));

				if (start == prim)
					prim = urm.get(start);

				if (primLiber != -1)
					prec.set(primLiber, start);

				dealoca(start);

			}
			else if (elem == e.get(end)) {
				e.set(end, NOVALUE);

				if (prec.get(end) != -1)
					urm.set(prec.get(end), urm.get(end));

				if (urm.get(end) != -1)
					prec.set(urm.get(end), prec.get(end));


				if (end == prim)
					prim = urm.get(end);

				if (primLiber != -1)
					prec.set(primLiber, end);

				dealoca(end);
			}


			start = urm.get(start);
			end = prec.get(start);
		}

		dimensiune--;
		return true;
	}


}

// Theta(n) : n - lungimea vectorilor dinamici
bool Multime::cauta(TElem elem) const {

	int start, end;
	start = prim;
	end = ultim;

	while (end != -1 && start != -1)
	{
		if (elem == e.get(start))
			return true;
		if (elem == e.get(end))
			return true;

		start = urm.get(start);
		end = prec.get(start);
	}

	return false;
}

// Theta(1)
int Multime::dim() const {
	/* de adaugat */
	return dimensiune;
}

// Theta(1)
bool Multime::vida() const {
	/* de adaugat */
	return dimensiune == 0 || prim == -1;
}

// Theta(1)
Multime::~Multime() {
	/* de adaugat */
}


// Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

