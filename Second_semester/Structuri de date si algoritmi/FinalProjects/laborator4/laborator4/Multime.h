#pragma once
#include "VectorDinamic.h"

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	/* Lista dublu inlantuita reprezentata pe tablou dinamic */

	int capacitate = 5;


	// Vector dinamic cu elemente de tip TElem
	myVector<TElem> e;

	// Vectori dinamici pt. legaturi
	myVector<TElem> urm;

	myVector<TElem> prec;

	// Referinta catre primul si ultimul element al listei
	int prim;
	int ultim;

	// Referinta catre primul element al listei spatiului liber
	int primLiber;

	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int aloca();

	//dealoca spatiul de indice i
	void dealoca(int i);

	//functie privata care creeaza un nod in lista inlantuita
	int creeazaNod(TElem e);

	// redimensioneaza vectorii si reseteaza spatiul liber
	void resetSpatiuLiber();

	// numarul de elemente din multime
	int dimensiune = 0;


public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};




