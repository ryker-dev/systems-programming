#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char * op;
    if ( (op = getenv("OPERATOR")) == NULL) {
        exit(1);
    }

    int result = atof(argv[1]);
    if (argc > 1) {
		for (int i = 2; i < argc; i++) {
			if (strcmp(op, "add") == 0) {
				result += atof(argv[i]);
			}
			if (strcmp(op, "mul") == 0) {
				result *= atof(argv[i]);
			}
		}
	}
    printf("Result: %d\n", result);
    return result;
}
