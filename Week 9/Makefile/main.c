#include <stdio.h>
#include "functions.h"

int main(int argc, char const *argv[]) {
    printf("Result: %d\n", sum(atoi(argv[1]), atoi(argv[2])));
    return 0;
}
