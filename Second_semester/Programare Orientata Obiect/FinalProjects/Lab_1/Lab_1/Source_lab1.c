/*
	Citeste un sir de numere naturale nenule terminat cu 0 si determina
	numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
*/
#include<stdio.h>

/*
	Functia produs() are rolul de a citi numere de la tastatura si de a le inmulti returnand produsul lor.
	:return: p
 */
int produs() {

	int x, c1 = 0, c2 = 0, s = 0;

	printf("Introdu primul numar: ");
	scanf_s("%d", &x);
	while (x != 0) {

		printf("Introdu urmatorul numar: ");
		scanf_s("%d", &x);

		if (div_cu_5(x) == 1)
			c1++;

		if (div_cu_2(x) == 1)
			c2++;

		if (c1 > 0 && c2 > 0) {
			s++;
			c1--;
			c2--;
		}
	}

	return s;
}

/*
	Functia nr_cif_0(int n) are rolul de a numara cate cifre 0 se afla in numarul n de tip intreg.
	:return: s - numarul cifrelor 0.
 */
int div_cu_5(int n) {
	if (n % 5 == 0)
		return 1;
	return 0;
}

int div_cu_2(int n) {
	if (n % 2 == 0)
		return 1;
	return 0;
}

int nr_cif_0(int n) {

	int s = 0, copie;
	copie = n;

	while (copie > 0) {
		if (copie % 10 == 0)
			s++;
		copie /= 10;
	}

	return s;
}

/*
	calculează valoarea lui sin(x) cu precizie _precision_
	x <- valoarea in care se calculează sinusul
	precision -> precizia cu care se calculeaza
		precision mare - precizie mare (>30 acceptabilă)
			de regulă precision = 100 oferă un răspuns
								satisfăcător
 */
double my_sin(double x, int precision) {

	double s = x;
	double numarator = x;
	double numitor = 1;

	int step = 2;
	int fact = 1;

	while (step <= precision) {
		float sgn = (step % 2 == 0) ? -1 : 1;
		numarator *= x * x;
		numitor *= (fact + 1) * (fact + 2);
		fact += 2;
		s += sgn * (numarator / numitor);
		step++;
	}
	return s;
}

void _ui_meniu() {

	int bucla = 1;

	while (bucla == 1) {
		int cmd;
		cmd = _ui();
		if (cmd == 1) {
			int p;
			p = produs();

			printf("Numarul cifrelor 0 al numarului %d este %d", p, nr_cif_0(p));
		}
		else if (cmd == 2) {
			int n = 0;
			double x = 0;

			printf("\nCiteste pe n: ");
			scanf_s("%d", &n);

			if (n == 0)
				return 0;

			printf("Citeste pe x: ");

			scanf_s("%lf", &x);

			printf("%.14f\n", my_sin(x, n));
		}
		else if (cmd == 0) {
			bucla = 0;
		}
		else {
			printf("\033[0;31m");
			printf("Comanda introdusa este gresita.\n");
		}
	}

}

int _ui() {
	int cmd;

	printf("\033[0;34m");
	printf("\n\nMeniu laborator 1\n");
	printf("\033[0;33m");
	printf("1. Numarul cifrelor 0 din produsul rezultat al numerelor cititie.\n");
	printf("2. Sume partiale.\n");
	printf("0. Iesi din aplicatie.\n");
	printf(">>> ");
	scanf_s("%d", &cmd);
	printf("\n");
	printf("\033[0;32m");

	return cmd;
}

int main() {
	
	_ui_meniu();

	return 0;
}