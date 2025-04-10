#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// the elements in the list
struct element {
    int data;
    struct element *next;
};

// a pointer to the head of the list
struct element *head;

// a temporary pointer used for freeing memory
struct element *temp;

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    if (argc != 2) {
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) <= 0) {
        fprintf(stderr,"Argument %d must be a positive number\n",atoi(argv[1]));
        return -1;
    }

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid,&attr,runner,argv[1]);

    /* now wait for the thread to exit */
    pthread_join(tid,NULL);

    struct element *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        temp = current;
        current = current->next;
        free(temp);
    }
    printf("\n");

    return 0;
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param)
{
    int n = atoi(param);
    struct element *node;

    node = (struct element *) malloc(sizeof(struct element));
    head = node;

    if (node == NULL) {
        fprintf(stderr, "Error: malloc failed.\n");
        pthread_exit(0);
    }

    while (n != 1) {
        // populate the list
        node->data = n;

        node->next = (struct element *) malloc(sizeof(struct element));

        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }

        node = node->next;
    }

    node->data = 1;
    node->next = NULL;

	pthread_exit(0);
}