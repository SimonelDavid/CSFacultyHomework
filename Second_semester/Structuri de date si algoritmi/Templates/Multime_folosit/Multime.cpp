#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: O(n)
 */
void Multime::redim() {
	//alocam un spatiu de capacitate dubla
	TElem* eNou = new int[2 * cp];

	//copiem vechile valori in noua zona
	for (int i = 0; i < n; i++)
		eNou[i] = e[i];

	//dublam capacitatea
	cp = 2 * cp;

	//eliberam vechea zona
	delete[] e;

	//vectorul indica spre noua zona
	e = eNou;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
Multime::Multime() {
	//setam capacitatea
	this->cp = 10;

	//alocam spatiu de memorare pentru vector
	e = new TElem[cp];

	//setam numarul de elemente
	this->n = 0;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: O(n)
 */
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

/*
 * caz favorabil = se efectueaza cautarea, dar elementul nu exista si atunci se preia complexitatea algoritmului de cautare si anume Θ(n)
 * caz defavorabil = elementul este gasit si se efectueaza stergerea va avea compleixtatea Θ(n^2)
 * caz mediu = in acest caz complexitatea medie este O(n^2)
 * complexitate timp: O(n^2)
 * complexitate spatiu: O(n^2)
 */
bool Multime::sterge(TElem elem) {
	if (cauta(elem) == false)
		return false;
	if (cauta(elem) == true) {
		for (int i = 0; i < n; i++) {
			if (elem == e[i]) {
				for (int j = i; j < n; j++)
					e[j] = e[j + 1];
				n--;
			}
		}
	}

	return true;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(n)
 * complexitate spatiu: O(n)
 */
bool Multime::cauta(TElem elem) const {
	for (int i = 0; i < n; i++) {
		if (e[i] == elem)
			return true;
	}
	return false;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
int Multime::dim() const {
	return n;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
bool Multime::vida() const {
	if (this->n == 0)
		return true;
	else
		return false;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
Multime::~Multime() {
	delete[] e;
}


/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: O(1)
 */
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

