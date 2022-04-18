#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREAD 10

int result = 0;
pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;

void * increment(void * par) {
    pthread_mutex_lock(&mt);
    int i;
    for (i = 0; i < *(int *)par; i++) {
        result++;
    }
    pthread_mutex_unlock(&mt);
}


int main() {
    pthread_t tid[NTHREAD];
    int i;
    int num = 1000;

    for (i = 0; i<NTHREAD; i++) {
            printf("Creating thread %d\n",i);
            pthread_create(& tid[i], NULL, increment, (void *)&num);
            pthread_join(tid[i], NULL);
    }

    printf("Value %d\n", result);
    pthread_mutex_destroy(&mt);
}
