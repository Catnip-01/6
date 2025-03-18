#include <stdio.h>
#include <dirent.h>
#include <string.h>

void print_file_type(const char *filename) {
    // Get the file extension
    const char *dot = strrchr(filename, '.');
    if (dot) {
        // Print the file extension
        printf("File: %s, Extension: %s\n", filename, dot + 1);
    } else {
        printf("File: %s, No extension found\n", filename);
    }
}

int main() {
    DIR *d;
    struct dirent *dir;

    // Open the current directory
    d = opendir(".");
    if (d) {
        printf("Listing all files in the current directory:\n");

        // Read all the entries in the directory
        while ((dir = readdir(d)) != NULL) {
            // Skip the "." and ".." entries
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                print_file_type(dir->d_name);
            }
        }

        closedir(d);
    } else {
        printf("Could not open current directory.\n");
    }

    return 0;
}
