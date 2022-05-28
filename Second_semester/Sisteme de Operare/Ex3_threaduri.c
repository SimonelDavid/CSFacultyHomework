//Va crea UN SINGUR thread care:
//- va citi N numere întregi (pe 1 OCTET) din fișierul binar "/tmp/test-file"
//și le va stoca într-o variabilă globală;
//- va genera un număr aleator M (0 < M < 256).
//Va crea, apoi, un număr potrivit de thread-uri care vor procesa numerele
//care au fost citite din fișier în primul thread creat și care:
//- vor determina și afișa numărul de apariții ale numărului aleator M
//în fiecare interval de 200 de numere întregi consecutive;
//- vor calcula, la final, și vor stoca într-o variabilă globală comună,
//numărul total de apariții ale numărului aleator M.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>

int N;
int MAX_TH;
int MAX_SIZE = 200;
int ap = 0;

int* nums;
int M;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* god_work(void* args){
	nums = (int*)malloc(N*sizeof(int));
	int fd = open("file.bin", O_RDONLY);
	for(int i = 0; i < N; i++){
		read(fd, &nums[i], 1);
	}
	srandom(time(0));
	M = random() % 256;
	//M = 201; //de test
	printf("numărul generat: %d\n", M);
	return NULL;
}

void* angels_work(void* args){
	int index = (int)args;
	int start = index*MAX_SIZE;
	int end = (index+1)*MAX_SIZE;
	int ap_local = 0;
	for(int i = start; i < end; i++){
		if(nums[i] == M)ap_local++;
	}
	pthread_mutex_lock(&mtx);
		ap+=ap_local;
	pthread_mutex_unlock(&mtx);
	free(args);
	return NULL;
}

int main(int argc, char** argv){
	if(argc != 2){
		printf("trebe dat un nr N multiplu de 200\n");
		return 1;
	}
	N = atoi(argv[1]);
	MAX_TH = N/200;
	pthread_t tid[MAX_TH];

	pthread_t god;
	pthread_create(&god, NULL, god_work, NULL);
	pthread_join(god, NULL);

	for(int i = 0; i < MAX_TH; i++){
		int* p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[i], NULL, angels_work, p);
	}
	for(int i = 0; i < MAX_TH; i++){
		pthread_join(tid[i], NULL);
	}
	printf("aparitii: %d\n", ap);
	return 0;
}