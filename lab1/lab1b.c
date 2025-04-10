#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[] = {"./collatz", argv[1], NULL};
        execvp(args[0], args);
        // If execvp fails
        fprintf(stderr, "Error: exec failed.\n");
        return 1;
    } else {
        // Parent process
        wait(NULL); // Wait for the child to complete
        printf("Child process completed.\n");
    }

    return 0;
}

