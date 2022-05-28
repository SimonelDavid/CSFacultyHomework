#include "IteratorColectie.h"
#include "Colectie.h"

using namespace std;

// complexitate: O(n) - capacitatea curenta a colectiei
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = col.rad;
	int anterior = -1;
	// se adauga in stiva ramura stanga a elementului curent
	while (curent != -1) {
		s.push(curent);
		anterior = curent;
		curent = col.stang[curent];
	}
	// se sterge frunza din varful stivei
	if (!s.empty()) {
		s.pop();
		curent = anterior;
	}
}

// complexitate: theta(1)
TElem IteratorColectie::element() {
	if (!valid()) {
		throw exception();
	}
	return col.elems[curent].first;
}

// complexitate: theta(1)
bool IteratorColectie::valid() const {
	return curent != -1;
}

// complexitate: O(n) - capacitatea curenta a colectiei
void IteratorColectie::urmator() {
	if (!valid()) {
		throw exception();
	}
	// stergem nodul din varful stivei
	if (!s.empty()) {
		curent = s.top();
		s.pop();
	}
	if (col.drept[curent] != -1) {
		curent = col.drept[curent];
		// adaugam in stiva ramura stanga a elementului curent
		while (curent != -1) {
			s.push(curent);
			curent = col.stang[curent];
		}
	}
	// se sterge nodul din varful stivei
	if (!s.empty()) {
		curent = s.top();
	}
	else {
		curent = -1;
	}
}

// complexitate: O(n) - capacitatea curenta a colectiei
void IteratorColectie::prim() {
	// stergem toate elementele adaugate din stiva
	while (!s.empty()) {
		s.pop();
	}
	curent = col.rad;
	// se adauga in stiva ramura stanga a elementului curent
	while (curent != -1) {
		s.push(curent);
		curent = col.stang[curent];
	}
	// se sterge frunza din varful stivei
	if (!s.empty()) {
		s.pop();
		curent = s.top();
	}
}