#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char filepath[1024];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip current and parent directories
        }

        snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name); //create the full file path.

        if (stat(filepath, &fileStat) == 0) {
            if (S_ISREG(fileStat.st_mode) && fileStat.st_size == 0) {
                if (unlink(filepath) == 0) {
                    printf("Removed empty file: %s\n", filepath);
                } else {
                    perror("unlink");
                }
            }
        } else {
            perror("stat");
        }
    }

    closedir(dir);
    return 0;
}