#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	/* de adaugat */
	curent = m.prim;
}


void IteratorMultime::prim() {
	/* de adaugat */
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	/* de adaugat */
	curent = multime.urm[curent];
}


TElem IteratorMultime::element() const {
	/* de adaugat */
	return multime.e[curent];
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	return curent != -1;
}
