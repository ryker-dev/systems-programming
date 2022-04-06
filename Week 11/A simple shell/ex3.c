#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFERSIZE 80

char** parse_tokens(char* cline) {
    char **args = malloc(BUFFERSIZE * sizeof(char*));
    char *token;

    token = strtok(cline, " ");

    int i = 0;
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    return args;
}

int main(int argc, char const **argv)
{
    char cline[BUFFERSIZE];
    char **args;
    int pid;

    while (1) {
        printf("> ");
        fgets(cline,BUFFERSIZE,stdin);
        cline[strcspn(cline, "\n")] = 0;
        args = parse_tokens(cline);

        if (!strcmp(args[0], "exit")) {
            exit(0);
        }

        switch (pid = fork()) {
        case -1:
            perror("Error in fork");
            exit(1);
        case 0:    
            execvp(args[0], args);
        default:
            wait(NULL);
        }
    }
    
    return 0;
}
