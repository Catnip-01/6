#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    const char *dirname = "my_directory"; // Replace with your desired directory name
    mode_t mode = 0755; // Permissions: rwxr-xr-x

    if (mkdir(dirname, mode) == 0) {
        printf("Directory '%s' created successfully.\n", dirname);
    } else {
        perror("Error creating directory");
        return 1; // Indicate failure
    }

    return 0; // Indicate success
}