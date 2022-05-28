//
// barrier.c - Using barriers
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

#define THR_NUM 10    // number of threads
#define VAL_NUM 5     // numbers of integers in the array
#define SIZE 2000

int *nums;

pthread_barrier_t barr;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
//
// Thread routine
//

int max(int a, int b){
    if(a < b)
        return b;
    else
        return a;
}

void* do_work(void* a)
{
    int id = *(int*)a;
    free(a);

    sleep(2);

    pthread_mutex_lock(&mtx);

    int maximum = -1000;
    int start = id*100;
    int end = (id+1)*100;
    int i;
    for(i = start; i < end; i++){
        maximum = max(maximum, nums[i]);
//      printf("nums[%2d]: ", i);
//      printf("%2d\n", nums[i]);
    }
 }

    printf("[THREAD %2d]: ", id);
    printf("maximul din intervalul %2d ", start);
    printf("- %2d ", end-1);
    printf("este %2d \n", maximum);

    pthread_mutex_unlock(&mtx);

    // wait until each thread execute the code above this point
    pthread_barrier_wait(&barr);

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_barrier_init(&barr, NULL, THR_NUM);     // init the barrier

    nums = (int*)malloc(1*sizeof(int));
    int i;
    int fd = open("file.bin", O_RDONLY);
    for(i = 0; i < 1000; i++){
        read(fd, &nums[i], 1);
    }

    pthread_t tid[THR_NUM];
    for (i = 0; i < THR_NUM; i++)
    {
        int *id = (int*)malloc(1 * sizeof(int));
        *id = i;

        int rc = pthread_create(&tid[i], NULL, do_work, id);
        if (rc != 0)
            printf("Unable to create thread %2d\n", id);
    }

    printf("The threads were created.\n");

    for (i = 0; i < THR_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }


    pthread_barrier_destroy(&barr);                 // destroy the barrier

    return 0;
}
