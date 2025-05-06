#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(){
    struct stat file;
    struct dirent *entry;
    DIR *dir = opendir(".");

    while ((entry = readdir(dir)) != NULL){
        if (stat(entry->d_name, &file) == 0){
            printf("%lu %o %s\n", file.st_ino, file.st_mode, entry->d_name);
        }
        
    }

    closedir(dir);
    return 0;
}