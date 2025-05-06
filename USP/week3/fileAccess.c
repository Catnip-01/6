#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    // Check and print file permissions (rwx for owner, group, others)
    printf("Permissions: ");
    
    // Owner
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    // Group
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    // Others
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");

    printf("\n");
}

int main() {
    struct stat fileStat;
    const char *filename = "fileTypes.c";  // Specify your file name here

    // Get the file status
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    // Print the file permissions
    print_permissions(fileStat.st_mode);

    return 0;
}
