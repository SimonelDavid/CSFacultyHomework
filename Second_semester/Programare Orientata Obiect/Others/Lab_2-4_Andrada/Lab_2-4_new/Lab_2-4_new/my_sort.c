#include "my_sort.h"


/**
* Sorteaza in place
* cmpf - relatia dupa care se sorteaza
*/
void sort(MyList* l, FunctieComparare cmpF) {
	int i, j;
	for (i = 0; i < size(l); i++) {
		for (j = i + 1; j < size(l); j++) {
			Car masina1 = get(l, i);
			Car masina2 = get(l, j);
			if (cmpF(&masina1, &masina2) > 0) {
				//interschimbam
				set(l, i, masina2);
				set(l, j, masina1);
			}
		}
	}
}