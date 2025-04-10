#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

    int i;
    unsigned int number;
    const int OFFSET_MASK = 0x3ff;
    const int PAGE_MASK = 0xfffc00;

    // get the numbers we are passed on the command line
    for (i = 1; i < argc; i++) {
        number = atoi(argv[i]);

        // AND number with MASK
        int offset = number & OFFSET_MASK;

        int page_number = number & PAGE_MASK;
        page_number = page_number >> 10;

        printf("Number = %d page number = %d offset = %d\n", number, page_number, offset);
    }

    return 0;
}
