#include "Colectie.h"
#include "IteratorColectie.h"

#include <iostream>

using namespace std;

// complexitate: theta(1)
bool rel(TElem e1, TElem e2) {
	return e1 <= e2;
}

// complexitate: O(n) - capacitatea curenta a colectiei
void Colectie::resize() {
	// redimensionarea pentru cele 3 tablouri
	TComparabil* new_elems = new TComparabil[cp * 2];
	int* new_drept = new int[cp * 2];
	int* new_stang = new int[cp * 2];
	for (int i = 0; i < cp; i++) {
		new_elems[i] = elems[i];
		new_drept[i] = drept[i];
		new_stang[i] = stang[i];
	}
	// dealocarea spatiului pentru tablourile anterioare si initializarea lor
	delete elems;
	delete drept;
	delete stang;
	elems = new_elems;
	drept = new_drept;
	stang = new_stang;
	// reinitializarea listei de spatii libere
	for (int i = cp; i < cp * 2 - 1; i++) {
		drept[i] = i + 1;
	}
	stang[cp * 2 - 1] = -1;
	primLiber = cp;
	cp = cp * 2;
}

// complexitate: theta(1)
int Colectie::aloca() {
	// alocam un spatiu pe prima pozitie libera
	int p = primLiber;
	primLiber = drept[primLiber];
	return p;
}

// complexitate: theta(1)
void Colectie::dealoca(int p) {
	drept[p] = primLiber;
	stang[p] = -1;
	primLiber = p;
}

// complexitate: O(n) - capacitatea curenta a colectiei
int Colectie::creeazaNod(TElem e) {
	if (size >= cp) {
		resize();
	}
	int p = aloca();
	elems[p] = std::make_pair(e, 1);
	stang[p] = -1;
	drept[p] = -1;
	return p;
}

// complexitate: O(n) - capacitatea initala a colectiei
Colectie::Colectie() {
	cp = CAPACITY;
	size = 0;
	// alocam spatiu pentru cele 3 liste
	elems = new TComparabil[cp];
	stang = new int[cp];
	drept = new int[cp];
	// initializam colectia vida
	rad = -1;
	// intializam spatiile libere in lista
	for (int i = 0; i < cp - 1; i++) {
		drept[i] = i + 1;
		stang[i + 1] = i;
	}
	stang[0] = -1;
	drept[cp - 1] = -1;
	// primul sptiu liber este pe indexul 0
	primLiber = 0;
}

// complexitate: O(n) - capacitatea curenta a arborelui
void Colectie::adauga(TElem e) {
	size++;
	// daca colectia e vida
	if (rad == -1) {
		rad = creeazaNod(e);
		return;
	}
	// parcurgem arborele pana gasim locul de adaugat
	int pos = rad;
	int parent = pos;
	while (pos != -1) {
		parent = pos;
		// daca elementul exista deja incrementam frecventa
		if (e == elems[pos].first) {
			elems[pos].second++;
			return;
		}
		// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
		if (rel(e, elems[pos].first)) {
			pos = stang[pos];
		}
		else {
			pos = drept[pos];
		}
	}
	// creem noul nod si subarborii
	int p = creeazaNod(e);
	if (rel(e, elems[parent].first)) {
		stang[parent] = p;
	}
	else {
		drept[parent] = p;
	}
}

// complexitate: O(n) - capacitatea curenta a arborelui
int Colectie::minim(int p) {
	while (p != -1) {
		p = stang[p];
	}
	return p;
}

// complexitate: O(n) - capacitatea curenta a arborelui
bool Colectie::sterge_rec(int curent, int anterior, TElem e) {
	// daca am ajuns la un subarbore vid
	if (curent == -1) {
		return false;
	}
	// daca am ajuns la elementul de sters
	if (elems[curent].first == e) {
		size--;
		// daca elementul are mai mult de o singura aparitie, decrementam frecventa
		if (elems[curent].second > 1) {
			elems[curent].second--;
			return true;
		}
		// daca nodul are si subarbore stang si drept
		else if (stang[curent] != -1 && drept[curent] != -1) {
			int min = minim(drept[curent]);
			elems[curent] = elems[min];
			return sterge_rec(drept[curent], curent, elems[min].first);
		}
		// daca nodul este o frunza
		else if (stang[curent] == -1 && drept[curent] == -1) {
			if (curent == rad) {
				rad = -1;
			}
			else {
				if (stang[anterior] == curent) {
					stang[anterior] = -1;
				}
				else {
					drept[anterior] = -1;
				}
			}
		}
		// daca nodul are un singur fiu, stang
		else if (stang[curent] == -1) {
			if (anterior == -1) {
				rad = drept[curent];
			}
			else if (stang[anterior] == curent) {
				stang[anterior] = drept[curent];
			}
			else {
				drept[anterior] = drept[curent];
			}
		}
		// daca nodul are un singur fiu, drept
		else {
			if (anterior == -1) {
				rad = stang[curent];
			}
			else if (stang[anterior] == curent) {
				stang[anterior] = stang[curent];
			}
			else {
				drept[anterior] = stang[curent];
			}
		}
		dealoca(curent);
		return true;
	}
	// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
	if (rel(e, elems[curent].first)) {
		return sterge_rec(stang[curent], curent, e);
	}
	else {
		return sterge_rec(drept[curent], curent, e);
	}
}

// complexitate: O(n) - adancimea curenta a arborelui
bool Colectie::sterge(TElem e) {
	return sterge_rec(rad, -1, e);
}

// complexitate: O(n) - capacitatea curenta a arborelui
int Colectie::stergeToateElementeleRepetitive() {
	int rez = 0;
	// daca colectia e vida
	if (rad == -1) {
		return rez;
	}
	// parcurgem arborele pana gasim locul cu element duplicat
	int pos = rad;
	while (pos != -1) {
		TElem e = elems[pos].first;
		int pos1 = rad;
		while (pos1 != -1) {
			// daca elementul exista deja stergem toate duplicatele lui
			TElem elem = elems[pos1].first;
			if (e == elem) {
				rez = elimina_rec(pos1, -1, e);
				pos1 = rad;
			}
			// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
			if (rel(e, elems[pos1].first)) {
				pos1 = stang[pos1];
			}
			else {
				pos1 = drept[pos1];
			}
		}
		// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
		if (rel(e, elems[pos].first)) {
			pos = stang[pos];
		}
		else {
			pos = drept[pos];
		}
	}
	if (rez == -1) {
		return 0;
	}
	if (rez > 0) {
		return 1;
	}
	return rez;
}


// complexitate: O(n) - capacitatea curenta a arborelui
int Colectie::elimina_rec(int curent, int anterior, TElem e) {
	// daca am ajuns la un subarbore vid
	if (curent == -1) {
		return 0;
	}
	// daca am ajuns la elementul de sters
	if (elems[curent].first == e) {
		size--;
		int nrAp;
		// daca nodul are si subarbore stang si drept
		if (stang[curent] != -1 && drept[curent] != -1) {
			nrAp = elems[curent].second;
			int min = minim(drept[curent]);
			elems[curent] = elems[min];
			sterge_rec(drept[curent], curent, elems[min].first);
			return nrAp;
		}
		// daca nodul este o frunza
		else if (stang[curent] == -1 && drept[curent] == -1) {
			if (curent == rad) {
				rad = -1;
			}
			else {
				if (stang[anterior] == curent) {
					stang[anterior] = -1;
				}
				else {
					drept[anterior] = -1;
				}
			}
		}
		// daca nodul are un singur fiu, stang
		else if (stang[curent] == -1) {
			if (anterior == -1) {
				rad = drept[curent];
			}
			else if (stang[anterior] == curent) {
				stang[anterior] = drept[curent];
			}
			else {
				drept[anterior] = drept[curent];
			}
		}
		// daca nodul are un singur fiu, drept
		else {
			if (anterior == -1) {
				rad = stang[curent];
			}
			else if (stang[anterior] == curent) {
				stang[anterior] = stang[curent];
			}
			else {
				drept[anterior] = stang[curent];
			}
		}
		nrAp = elems[curent].second;
		dealoca(curent);
		return nrAp;
	}
	// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
	if (rel(e, elems[curent].first)) {
		return elimina_rec(stang[curent], curent, e);
	}
	else {
		return elimina_rec(drept[curent], curent, e);
	}
}

// complexitate: O(n) - capacitatea curenta a arborelui
bool Colectie::cauta(TElem elem) const {
	// parcurgem arborele pana gasim elementul sau ajungem la capatul arborelui
	int pos = rad;
	while (pos != -1) {
		if (elem == elems[pos].first) {
			return true;
		}
		// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
		if (rel(elem, elems[pos].first)) {
			pos = stang[pos];
		}
		else {
			pos = drept[pos];
		}
	}
	return false;
}

// complexitate: O(n) - capacitatea curenta a arborelui
int Colectie::nrAparitii(TElem elem) const {
	// parcurgem arborele
	int pos = rad;
	while (pos != -1) {
		// daca am gasit elementul
		if (elem == elems[pos].first) {
			return elems[pos].second;
		}
		// daca este in relatie cu elementul curent parcurgem subarborele stang, altfel pe cel drept
		if (rel(elem, elems[pos].first)) {
			pos = stang[pos];
		}
		else {
			pos = drept[pos];
		}
	}
	// daca elementul nu a fost gasit
	return 0;
}

// complexitate: theta(1)
int Colectie::dim() const {
	return size;
}

// complexitate: theta(1)
bool Colectie::vida() const {
	return size == 0;
}

// complexitate: O(n) - capacitatea curenta a colectiei
IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}

// complexitate: theta(1)
Colectie::~Colectie() {
	delete[] elems;
	delete[] stang;
	delete[] drept;
}