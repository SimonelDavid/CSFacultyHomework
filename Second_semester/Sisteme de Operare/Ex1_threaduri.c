//1. Scrieți un program C care primește în linia de comandă oricâte perechi de argumente formate dintr-un nume de fișier și o cifră, astfel:./ex1 a.txt 3 b.txt 3 ...Programul va utiliza un vector cu 10 numere întregi ca variabilă globală și pentru fiecare pereche de argumente furnizată în linia de comandă, programul va crea câte un thread. Fiecare thread va determina și va adăuga numărul de litere mari din fișierul dat la numărul întreg a cărui poziție este egală cu cifra primită ca argument.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct pereche{
	char* fisier;
	char* cifra;
}pereche;

int cif[10];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* work(void* arg){
	pereche p = *(pereche*)arg;
	//printf("%s %s\n", p.fisier, p.cifra);
	int fd = open(p.fisier, O_RDONLY);
	if(fd < 0){
		printf("eroare la deschiderea lui %s\n",
					p.fisier);
		return NULL;
	}
	char b;
	int ap=0;
	while(read(fd, &b, 1)){
		if( b >= 'A' && b <= 'Z')ap++;
	}
	pthread_mutex_lock(&mtx);
	cif[atoi(p.cifra)]+=ap;
	pthread_mutex_unlock(&mtx);
	close(fd);
	free(arg);
	return NULL;
}

int main(int argc, char** argv){
	if(argc % 2 == 0 || argc == 1){
		printf("trebuie perechi [fisier cifra]\n");
		return 1;
	}
	pthread_t tid[(argc-1)/2];
	int i;
    for(i = 1; i < argc-1; i+=2){
		pereche* p = (pereche*)malloc(sizeof(pereche));
		p->fisier = argv[i];
		p->cifra = argv[i+1];
		pthread_create(&tid[i/2], NULL, work, p);
	}
	for(i = 1; i < argc-1; i+=2){
		pthread_join(tid[i/2], NULL);
	}
	for(i = 0; i < 10; i++)
		printf("pozitia %d; valoarea: %d\n", i, cif[i]);
	return 0;
}