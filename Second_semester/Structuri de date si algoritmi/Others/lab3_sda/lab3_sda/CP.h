#pragma once
#include <vector>
#include <utility>

using namespace std;

class Nod;

typedef int TElem;
typedef int TPrioritate;
//se defineste tipul PNod ca fiind adresa unui Nod
typedef Nod* PNod;

typedef std::pair<TElem, TPrioritate> Element;

typedef bool (*Relatie)(TPrioritate p1, TPrioritate p2);

class Nod

{

public:

	friend class Cp;

	//constructor

	PNod urm;
	PNod pre;
	

	Nod(Element e, PNod urm,PNod prec);

	PNod urmator();

	PNod anterior();

	Element element();
	Element e;
	

private:

	

};


class CP {
private:

	/* aici reprezentarea */
	//prim este adresa primului Nod din lista
	PNod prim;
	Relatie rela;


public:
	//constructorul implicit
	CP(Relatie r);

	//adauga un element in CP
	void adauga(TElem e, TPrioritate p);

	//acceseaza elementul cel mai prioritar in raport cu relatia de ordine
	//arunca exceptie daca CP e vida
	Element element()  const;

	//sterge elementul cel mai prioritar si il returneaza
	//arunca exceptie daca CP e vida
	Element sterge();

	//verifica daca CP e vida;
	bool vida() const;

	// destructorul cozii
	~CP();

};
