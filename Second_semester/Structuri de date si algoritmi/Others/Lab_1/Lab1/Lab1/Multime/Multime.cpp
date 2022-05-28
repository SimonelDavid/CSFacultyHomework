#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

Multime::Multime(int cp) {
	//setam capacitatea
	this->cp = cp;

	//alocam spatiu de memorare pentru vector
	e = new TElem[cp];

	//setam numarul de elemente
	this->n = 0;
}


bool Multime::adauga(TElem elem) {
	if (n == cp)
		redim();

	//verificam daca exista

	for (int i = 0; i < n; i++) {
		if (e[i] == elem)
			return false;
	}

	//adaugam la sfarsit
	this->e[n++] = elem;
	return true;
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	return false;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	return false;
}


int Multime::dim() const {
	/* de adaugat */
	return 0;
}

bool Multime::vida() const {
	if (this->n == 0)
		return true;
	else
		return false;
}


Multime::~Multime() {
	/* de adaugat */
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

