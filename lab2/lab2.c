#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <starting number> <shared memory name>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Error: Starting number must be a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) { // CHILD PROCESS (Producer)
        const int SIZE = 4096;
        int shm_fd;
        void *ptr;

        char shmName[256];
        sprintf(shmName, "/%s", argv[2]);

        shm_fd = shm_open(shmName, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            printf("shared memory failed\n");
            exit(-1);
        }

        if (ftruncate(shm_fd, SIZE) == -1) {
            printf("ftruncate failed\n");
            exit(-1);
        }

        ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            printf("Map failed\n");
            exit(-1);
        }

        char *temp = (char *)ptr;
        while (n != 1) {
            temp += sprintf(temp, "%d ", n);
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
        }
        sprintf(temp, "%d ", 1);

        return 0;
    }
    else { // PARENT PROCESS (Consumer)
        const int SIZE = 4096;
        int shm_fd;
        void *ptr;

        wait(NULL);

        char shmName[256];
        sprintf(shmName, "/%s", argv[2]);

        shm_fd = shm_open(shmName, O_RDONLY, 0666);
        if (shm_fd == -1) {
            printf("shared memory failed\n");
            exit(-1);
        }

        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        if (ptr == MAP_FAILED) {
            printf("Map failed\n");
            exit(-1);
        }

        printf("%s\n", (char *)ptr);

        if (shm_unlink(shmName) == -1) {
            printf("Error removing %s\n", shmName);
            return -1;
        }
    }

    return 0;
}
