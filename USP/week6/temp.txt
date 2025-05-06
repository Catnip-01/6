#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    char ch;

    // Check for the correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file in read mode
    src = fopen(argv[1], "rb");
    if (src == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file in write mode
    dest = fopen(argv[2], "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);  // Close the source file before exiting
        exit(EXIT_FAILURE);
    }

    // Copy the contents from source to destination
    while ((ch = fgetc(src)) != EOF) {
        if (fputc(ch, dest) == EOF) {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            exit(EXIT_FAILURE);
        }
    }

    printf("File copied successfully from '%s' to '%s'.\n", argv[1], argv[2]);

    // Close both files
    fclose(src);
    fclose(dest);

    return 0;
}
