#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/* de adaugat */
	prim = -1;

	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;

	primLiber = 0;
}

int Multime::aloca() {
	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

void Multime::dealoca(int i) {
	//se trece pozitia i in lista spatiului liber
	urm[i] = primLiber;
	primLiber = i;
}

int Multime::creeazaNod(TElem e) {
	//daca s-ar foosi vector dinamic, s-ar redimensiona in cazul in care colectia ar fi plina (primLiber=0)
	int i = aloca();
	if (i != -1) {//exista spatiu liber in lista
		this->e[i] = e;
		urm[i] = -1;
	}
	return i;
}

bool Multime::adauga(TElem elem) {
	/* de adaugat */
	int i = creeazaNod(elem);
	//in cazul folosirii unui vector static, e posibil ca i sa iasa -1 in cazul in care lista e plina
	if (i != -1) {
		urm[i] = prim;
		prim = i;
	}
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
	/* de adaugat */
	return true;
}


Multime::~Multime() {
	/* de adaugat */
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

