#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "example.txt";

    // Demonstrating access() function
    printf("Checking file access using access() function...\n");

    // Check if the file exists and if we have read and write permissions
    if (access(filename, F_OK) == 0) {
        printf("File '%s' exists.\n", filename);

        // Check if the file is readable
        if (access(filename, R_OK) == 0) {
            printf("File '%s' is readable.\n", filename);
        } else {
            printf("File '%s' is not readable.\n", filename);
        }

        // Check if the file is writable
        if (access(filename, W_OK) == 0) {
            printf("File '%s' is writable.\n", filename);
        } else {
            printf("File '%s' is not writable.\n", filename);
        }

        // Check if the file is executable
        if (access(filename, X_OK) == 0) {
            printf("File '%s' is executable.\n", filename);
        } else {
            printf("File '%s' is not executable.\n", filename);
        }
    } else {
        printf("File '%s' does not exist.\n", filename);
    }

    // Demonstrating umask() function
    printf("\nDemonstrating umask()...\n");

    // Get the current umask
    mode_t old_umask = umask(0);  // Get the current umask without changing it
    umask(old_umask);  // Restore the original umask value

    printf("Current umask value: %03o\n", old_umask);

    // Change the umask (set permissions to create files without write permissions for group and others)
    umask(S_IWGRP | S_IWOTH);
    printf("Umask set to restrict write permissions for group and others.\n");

    // Create a new file with restricted permissions
    int fd = open("new_file.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating new file");
        return 1;
    }
    close(fd);

    printf("New file 'new_file.txt' created with restricted permissions.\n");

    // Demonstrating chmod() function
    printf("\nDemonstrating chmod()...\n");

    // Change file permissions of 'new_file.txt' to rw-r--r--
    if (chmod("new_file.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Error changing file permissions");
        return 1;
    }

    printf("Permissions for 'new_file.txt' changed to rw-r--r--.\n");

    return 0;
}
