//2. Să se scrie un program C care:
//- va citi 200000 numere întregi (pe 1 OCTET) dintr-un fișierul binar și le va stoca într-o variabilă globală;
//- va crea, apoi, un număr potrivit de thread-uri care vor procesa numerele întregi citite anterior din fișier și care vor determina și vor afișa numărul mediu de apariții al unui număr prim din intervalul [1, 100].

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>

#define SIZE 200000
#define MAX_PRIME 100
#define PRIMES 25

int num[SIZE];

int prim(int n){
	if(n < 2)return 0;
	for(int i = 2; i <= n/2; i++)
		if(n % i == 0)return 0;
	return 1;
}

int suma;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* work(void* args){
	int p = *(int*)args;
	//printf("%d\n", p);
	int s_local = 0;
	for(int i = 0; i < SIZE; i++)
		if(num[i]==p)s_local++;
	pthread_mutex_lock(&mtx);
	suma += s_local;
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(int argc, char** argv){
	int fd = open("file.bin", O_RDONLY);
	pthread_t tid[PRIMES];
	for(int i = 0; i < SIZE; i++){
		read(fd, &num[i], 1);
	}
	int* p = (int*)malloc(sizeof(int));
	*p = 2;
	pthread_create(&tid[0], NULL, work, p);
	int k = 1;
	for(int i = 3; i < 100; i+=2){
		if(prim(i)){
			int* pp = (int*)malloc(sizeof(int));
			*pp= i;
			pthread_create(&tid[k], NULL, work, pp);
			k++;
		}
	}
	for(int i = 0; i < PRIMES; i++)
		pthread_join(tid[i], NULL);
	printf("%f\n", (double)suma/25);
	return 0;
}