#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PATH "/tmp/temp"

void deleteFile() {
    int code = unlink(PATH);
    if (code != 0) {
        printf("%s\n", strerror(errno));
        exit(errno);
    }
    printf("File unlinked\n");
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen(PATH, "w");
    unlink(PATH);
    //atexit(deleteFile);

    for (size_t i = 0; i < 30; i++)
    {
        fputs("Line\n", f);
        sleep(1);
    }
    fclose(f);

    return 0;
}
