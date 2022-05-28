#include "IteratorMultime.h"
#include "Multime.h"
#include "VectorDinamic.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = m.prim;
}


void IteratorMultime::prim() {
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	curent = multime.urm.get(curent);
}


TElem IteratorMultime::element() const {
	return multime.e.get(curent);
}

bool IteratorMultime::valid() const {
	return curent != -1;
}

//Transformați iteratorul în unul bidirecțional.Adăugați operația următoare în clasa IteratorMultime.

//modifică elementul curent referit de iterator ca fiind elementul anterior din mulțime, sau, 
//în cazul în care elementul curent a fost primul, transformă iteratorul în unul nevalid 

// aruncă excepție în cazul în care iteratorul nu este valid 
// Complexitate Theta(1)
void IteratorMultime::anterior() {
	if (curent == -1)
		throw "anterior este invalid";
	else if (curent == multime.prim)
		curent = -1;
	else
		curent = multime.prec.get(curent);
}