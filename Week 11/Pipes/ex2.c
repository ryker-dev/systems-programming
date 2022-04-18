#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define die(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0);

#define BUFSIZE 80
#define PIPE_READ 0
#define PIPE_WRITE 1

int main(int argc, char * * argv)
{
	FILE * fp;
	int i; 
	char buffer[BUFSIZE];
    int fd[2];
    pipe(fd);
	
	char command[BUFSIZE];

	command[0]='\0';
	/* concatenate arguments to one long string */
	for (i=1; i<argc; i++) {
		strcat(command,argv[i]);
		strcat(command," ");
	}
	
    int pid, status;
    switch (pid = fork()) {
    case -1:              /* error in fork */
        perror("Error in fork");
        exit(1);
    case 0:               /* child process */
        dup2(fd[PIPE_WRITE], STDOUT_FILENO);
        close(fd[PIPE_READ]);
        close(fd[PIPE_WRITE]);

        system(command);
        break;
    default:              /* parent process */
        close(fd[PIPE_WRITE]);

        int chars;
        while ((chars = read(fd[PIPE_READ], buffer, BUFSIZE - 1)) > 0) {
            if (chars < BUFSIZE - 1) {
                for(int i=0; i<chars; i++) {
                    printf("%c", buffer[i]);
                }
            break;
            }
            printf("%s", buffer);
        }

        close(fd[PIPE_READ]);
        break;
    }
	
	return 0;
}