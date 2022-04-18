#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include<signal.h>

#define PATH "temp.txt"
#define SIGINT 2

void deleteFile() {
    int code = unlink(PATH);
    if (code != 0) {
        printf("%s\n", strerror(errno));
        exit(errno);
    }
    printf("File unlinked\n");
    exit(2);
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen(PATH, "w");
    signal(SIGINT, deleteFile);
    atexit(deleteFile);

    for (size_t i = 0; i < 30; i++)
    {
        fputs("Line\n", f);
        sleep(1);
    }

    return 0;
}
