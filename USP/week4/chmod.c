#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    const char *filepath = "file1.txt"; // Replace with your file path
    mode_t new_permissions = S_IRUSR | S_IWUSR | S_IXUSR; // rwx for owner

    if (chmod(filepath, new_permissions) == 0) {
        printf("Permissions changed successfully.\n");
    } else {
        perror("Error changing permissions");
        return 1; // Indicate failure
    }

    return 0; // Indicate success
}