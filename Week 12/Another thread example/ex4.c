#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

/* declare as volatile to make sure the compiler does not optimize the variables to fixed values */
volatile double result=0.0;
volatile long long j=0;

/* approximation of pi/4 by Leibniz' series */
void * compute(void * par) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    while (j>=0) {      /* stop if j overflows */
        result = result + (pow(-1.0, j)/(2*j+1))*4;
        j++;
        usleep(100);    /* add this little delay just because the computation is
                                otherwise so fast that you get a good approximation in 1 second */
    }
    return NULL;
}

int main(int argc, char ** argv)
{
    pthread_t cid;
    int sec=10,c=0;

    if (argc==2)
        sec=atoi(argv[1]);

    if (pthread_create(&cid, NULL, compute, NULL) != 0) {
        perror("pthread_create");
        exit(1);
    }

    printf("Computing values for %d seconds\n",sec);
    while (c<sec) {
        printf("%f\n", result);
        sleep(1);
        c++;
    }
    pthread_cancel(cid);
    pthread_join(cid, NULL);
    return 0;
}