/**
 *  Simple program demonstrating shared memory in POSIX systems.
 *
 *  This is the consumer process
 * 
 * Compilation for Linux systems:
 *
 *  gcc -lrt -o shm-posix-consumer shm-posix-consumer.c
 *
 * This will generate an executable named "consumer"
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;

	if (argc != 2) {
		printf("Usage: ./consumer [shared memory segment name]\n");
		return -1;
	}

	// open the shared memory segment
	shm_fd = shm_open(argv[1], O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	// now map the shared memory segment in the address space of the process
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	// now read from the shared memory region
	printf("%s",(char *)ptr);

	// remove the shared memory segment
	if (shm_unlink(argv[1]) == -1) {
		printf("Error removing %s\n",argv[1]);
		exit(-1);
	}

	return 0;
}
