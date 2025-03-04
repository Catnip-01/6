#include "apue.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 4096

int main(void) {
    int n;
    char buf[BUFFSIZE];

    // Read from standard input until the end of the input or an error occurs
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        // Write the read data to standard output
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("write error\n");
        }
    }

    // If read returns an error
    if (n < 0) {
        printf("read error\n");
    }

    exit(0);
}
