#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

// Function to print file information
void print_file_info(const char *filename, struct stat *fileStat) {
    printf("Information for file: %s\n", filename);
    printf("File Size: %ld bytes\n", fileStat->st_size);
    printf("Number of Links: %ld\n", fileStat->st_nlink);
    printf("File inode: %ld\n", fileStat->st_ino);
    
    printf("File Permissions: ");
    printf((fileStat->st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat->st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat->st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat->st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat->st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat->st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat->st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat->st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

// Demonstrating lstat, fstat, and fstatat
int main() {
    const char *filename = "new_file.txt";
    const char *symlinkname = "symlink_example"; // Assuming this is a symlink
    struct stat fileStat;

    // Demonstrating lstat() - For symbolic links or regular files
    printf("Demonstrating lstat() for file %s:\n", filename);
    if (lstat(filename, &fileStat) == -1) {
        perror("lstat");
        return 1;
    }
    print_file_info(filename, &fileStat);

    // Demonstrating fstat() - Using file descriptor
    printf("\nDemonstrating fstat() for file %s:\n", filename);
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &fileStat) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }
    print_file_info(filename, &fileStat);

    close(fd);

    // Demonstrating fstatat() - For relative paths within a directory
    printf("\nDemonstrating fstatat() for file %s:\n", filename);
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // fstatat requires a directory file descriptor (from opendir)
    if (fstatat(dirfd(dir), filename, &fileStat, 0) == -1) {
        perror("fstatat");
        closedir(dir);
        return 1;
    }
    print_file_info(filename, &fileStat);

    closedir(dir);

    // Demonstrating lstat() for symbolic link (if symlink exists)
    if (symlink(symlinkname, "example_symlink") == -1) {
        perror("symlink creation failed");
        return 1;
    }

    printf("\nDemonstrating lstat() for symbolic link %s:\n", symlinkname);
    if (lstat("example_symlink", &fileStat) == -1) {
        perror("lstat");
        return 1;
    }
    print_file_info("example_symlink", &fileStat);

    return 0;
}
