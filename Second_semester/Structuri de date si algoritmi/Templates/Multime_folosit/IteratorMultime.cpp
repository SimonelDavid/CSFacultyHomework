#include "IteratorMultime.h"
#include "Multime.h"

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = 0;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
void IteratorMultime::prim() {
	/* de adaugat */
	curent = 0;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
void IteratorMultime::urmator() {
	/* de adaugat */
	curent++;
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
TElem IteratorMultime::element() const {
	/* de adaugat */
	return multime.e[curent];
}

/*
 * caz favorabil = caz defavorabil = caz mediu
 * complexitate timp: Θ(1)
 * complexitate spatiu: Θ(1)
 */
bool IteratorMultime::valid() const {
	/* de adaugat */
	return curent < multime.dim();
}
