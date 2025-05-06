#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filepath = "file1.txt"; // Replace with your file path

    if (access(filepath, F_OK) == 0) {
        printf("File '%s' exists.\n", filepath);

        if (access(filepath, R_OK) == 0) {
            printf("File '%s' is readable.\n", filepath);
        } else {
            perror("Read access denied");
        }

        if (access(filepath, W_OK) == 0) {
            printf("File '%s' is writable.\n", filepath);
        } else {
            perror("Write access denied");
        }

        if (access(filepath, X_OK) == 0) {
            printf("File '%s' is executable.\n", filepath);
        } else {
            perror("Execute access denied");
        }
    } else {
        if (errno == ENOENT) {
            printf("File '%s' does not exist.\n", filepath);
        }
        else{
            perror("File access error");
        }
    }

    return 0;
}