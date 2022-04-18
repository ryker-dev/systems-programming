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

void exit_program() {
    exit(0);
}

// Handler method taken from linuxartisan on GitHub.com
void handler(int sig) {
    int status;
    waitpid(-1, &status, 1);
}

int main(int argc, char const **argv)
{
    char cline[BUFFERSIZE];
    char **args;
    int pid;
    int background;
    int status;

    signal (SIGCHLD, handler);

    while (1) {
        
        printf("> ");
        alarm(15);
        fgets(cline, BUFFERSIZE, stdin);
        cline[strcspn(cline, "\n")] = 0;
        args = parse_tokens(cline);

        if (!strcmp(args[0], "exit")) {
            exit_program();
        }

        for (int i = 0; args[i] != NULL; i++) {
            if (!strcmp(args[i], "&")) {
                args[i] = NULL;
                background = 1;
            }
        }

        switch (pid = fork()) {
        case -1:
            perror("Error in fork");
            exit(1);
        case 0:
            execvp(args[0], args);
        default:
            if (background) {
                waitpid(pid, &status, 0);
            } else {
                wait(NULL);
            }
        }
    }
    
    return 0;
}
