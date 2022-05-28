
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <iostream>

using namespace std;

Nod::Nod(Element e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

PNod Nod::urmator() {
	return urm;
}

Element Nod::element() {
	return e;
}


CP::CP(Relatie r) {
	prim = nullptr;
	this->rela = r;
}

/*
subalgortim adauga(e, p) este {teta(1)}
	elem.first <- e
	elem.second <- p
	q <- Nod(ele, nil)

	Daca prim = nil
		prim = q
		return
	SfDaca

	copie <- prim
	anterior <- nil

	x <- copie.element().second

	CatTimp copie ≠ nil && rela(x, p)
		anterior <- copie
		copie <- copie.urmator()

		Daca copie ≠ nil
			x <- copie.element().second
		SfDaca
	SfCatTimp

	Daca copie = nil
		anterior.urm <- q
	altfel
		Daca anterior = nil
			q.urm <- prim
			prim = q
		altfel
			q.urm <- copie
			anterior.urm <- q
		SfDaca
	SfDaca
SfSubalgoritm
*/
void CP::adauga(TElem e, TPrioritate p) {
	Element elem;
	elem.first = e;
	elem.second = p;
	PNod q = new Nod(elem, nullptr);

	if (prim == nullptr) {
		prim = q;
		return;
	}

	PNod copie = prim;
	PNod anterior = nullptr;

	TPrioritate x = copie->element().second;
	while (copie != nullptr && rela(x, p)) {
		anterior = copie;
		copie = copie->urmator();
		if(copie != nullptr)
			x = copie->element().second;
	}

	if (copie == nullptr) {
		// nici un nod cu prioritate mai mica decat p (Caz 1)
		anterior->urm = q;
	}
	else {
		if (anterior == nullptr) {
			// toate nodurile au prioritate mai mica decat p (Caz 2)
			// adaugam la inceput
			q->urm = prim;
			prim = q;
		}
		else {
			// adaugam nodul q inainte de nodul cu prioritate mai mica decat p (Caz 3)
			q->urm = copie;
			anterior->urm = q;
		}
	}
}

/*
Subalgoritm element()
	Daca prim = nil
		arunca exceptie out_of_range("nu")
	SfDaca

	return prim.e
SfSubalgoritm
*/
Element CP::element() const {
	
	if (prim == nullptr)
	{
		throw out_of_range("nu");
	}

	return prim->e;
}

/*
Subalgoritm sterge() este {teta(1)}
	Daca prim = nil
		arunca exceptie out_of_range("nu")
	SfDaca

	urmator <- prim.urm
	copie <- prim.element()
	delete prim
	prim <- urmator

	return copie
SfSubalgoritm
*/
Element CP::sterge() {
	
	if (prim == nullptr)
	{
		throw out_of_range("nu");
	}
	PNod urmator = prim->urm;
	Element copie = prim->element();
	delete prim;
	prim = urmator;

	return copie;
}

bool CP::vida() const {
	
	if (prim == nullptr)
		return true;

	return false;
}


CP::~CP() {
	delete[] prim;
};

TPrioritate CP::schimbaPrioritate(TElem elem, TPrioritate prioritateNoua) {
	int gasit = 0;
	Element element;
	element.first = elem;
	element.second = prioritateNoua;

	if (prim == nullptr) {
		return -1;
	}

	PNod copie = prim;
	PNod anterior = nullptr;

	TPrioritate x = copie->element().second;
	while (copie != nullptr && copie->e.first != elem) {
		anterior = copie;
		copie = copie->urmator();
		if (copie != nullptr) {
			x = copie->element().second;
			copie->e.second = prioritateNoua;
		}
	}

	if (copie == nullptr) {
		return -1;
	}
	else {
		anterior->urm = copie;
		prim = anterior;
	}

	return x;
}