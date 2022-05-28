
#include "CP.h"
#include <exception>
#include <stdio.h>
#include <iostream>

using namespace std;

Nod::Nod(Element e, PNod urm, PNod pre) {
	this->e = e;
	this->urm = urm;
	this->pre = pre;
}

PNod Nod::urmator() {
	return urm;
}

PNod Nod::anterior() {
	return pre;
}

Element Nod::element() {
	return e;
}


CP::CP(Relatie r) {
	/* de adaugat */
	prim = nullptr;
	this->rela = r;	

}


void CP::adauga(TElem e, TPrioritate p) {
	Element elem;
	elem.first = e;
	elem.second = p;
	PNod q = new Nod(elem, nullptr, nullptr);
	int ok = 0;
	PNod copie = prim;
	while (prim != nullptr)
	{
		TPrioritate x = prim->element().second;
		

		if (rela(x, p))
		{
		
			
			PNod anterior = prim;
			prim = prim->urm;
			if (prim == nullptr)//daca prim a ajuns sa fie primul nod(nullptr) inseamna ca vom insera nodul q pe acea pozitie
			{
				anterior->urm = q;
				q->pre = anterior;
				q->urm = prim;
				prim = copie;
				break;
			}
			
		}
		else {
			
			//adaugam nodul pe pozitia corespunzatoare in coada
			q->urm = prim;
			
			if (prim->pre != nullptr)//daca ultimul element adaugat in coada nu are predecesor nici cel adaugat nu va avea
			{
				q->pre = prim->pre;
				PNod n = prim->pre;
				n->urm = q;
			}
			prim->pre = q;
			if (prim != copie)
			{
				prim = copie;
			}
			else
				prim = q;
			
			break;

		}
	}
	if (prim == nullptr)
	{
		q->urm = prim;
		prim = q;
	}
}


//arunca exceptie daca coada e vida
Element CP::element() const {
	/* de adaugat */
	if (prim == nullptr)
	{
		//cout << "Coada este vida";
		throw out_of_range("nu");
	}
	return prim->e;
	//return pair <TElem, TPrioritate>  (-1, -1);       // copy constructor
;
}

Element CP::sterge() {
	/* de adaugat */
	if (prim == nullptr)
	{
		throw out_of_range("nu");
	}
	PNod urmator = prim->urm;
	Element copie = prim->element();
	delete prim;
	prim = urmator;
	//prim->pre = nullptr;

	//return pair <TElem, TPrioritate>  (-1, -1);
	return copie;


}

bool CP::vida() const {
	/* de adaugat */
	if (prim == nullptr)
		return true;
	return false;
	
}


CP::~CP() {
	/* de adaugat */
};

