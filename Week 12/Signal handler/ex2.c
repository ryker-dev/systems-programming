#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SIGINT 2
int secs;

void cont() {
    int pid = fork();
    if (pid == 0) {
        for (secs; secs > 0; secs--)
        {
            printf("%d\n", secs);
            sleep(1);
        }
    } else {
        exit(2);
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, cont);

    if (argc < 2) {
        secs = 10;
    } else {
        secs = atoi(argv[1]);
    }

    for (secs; secs > 0; secs--)
    {
        printf("%d\n", secs);
        sleep(1);
    }

    return 0;
}
