#include<stdio.h>

int suma(int n) {
	int s = 0;

	for (int i = 1; i <= n; i++) {
		s += i;
	}

	return s;
}

void main() {

	int n;

	printf("Citeste numarul n: ");
	scanf_s("%d", &n);

	printf("Suma este: %d", suma(n));

}