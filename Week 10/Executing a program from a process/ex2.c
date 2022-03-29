#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 50

int main(int argc, char const *argv[]) {
    printf("----system----\n");
    char command[LENGTH];
    strcpy(command, argv[1]);
    for (int i = 2; i < argc; i++)
    {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    
    system(command);

    printf("\n----execvp----\n");
    execvp(argv[1], argv+1);
}
