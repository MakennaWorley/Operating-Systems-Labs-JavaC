#include <stdio.h>
#include <stdlib.h>

void generate_collatz(int n) {
    printf("Collatz sequence: %d ", n);
    while (n != 1) {
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
        printf("%d ", n);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <starting number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: Starting number must be a positive integer.\n");
        return 1;
    }

    generate_collatz(n);
    return 0;
}
