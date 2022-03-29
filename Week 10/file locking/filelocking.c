#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include <time.h>
#include <unistd.h>

/*
Usage: ./filelocking [filename]
*/

int main(int argc, char const *argv[])
{
    /* Opening the file */
    int fd = open(argv[1], O_RDWR);
    if(fd == -1) {
            printf("Unable to open the file\n");
            exit(1);
    }

    time_t t;
    int pid = getpid();

    /* Locking and printing */
    time(&t);
    printf("pid: %3d, getting exclusive lock at %s", pid, ctime(&t));
    flock(fd, LOCK_EX);
    time(&t);
    printf("pid: %4d, exclusive locked at %s", pid, ctime(&t));
    sleep(20);

    /* Unlocking the file and printing */
    flock(fd, LOCK_UN);
    time(&t);
    printf("pid: %4d, unlocked at %s", pid, ctime(&t));   
    return 0;
}

