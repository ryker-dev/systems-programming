#include <stdio.h>

#define LENGHT(a)   (sizeof(a)/sizeof(a[0]))

int main(int argc, char const *argv[], char *envp[])
{
    printf("Parameters: ");

    for (int i = 0; i < argc; i++) {
        printf("\n%s", argv[i]);
    }
    
    printf("\n\nEnvironment variables: ");

    for (int i = 0; i < LENGHT(&envp); i++) {
        printf("\n%s", envp[i]);
    }
    printf("\n");

    return 0;
}