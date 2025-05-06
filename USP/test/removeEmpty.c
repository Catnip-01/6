#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main(){
    struct stat file;
    DIR *dir = opendir(".");
    struct dirent *entry;

    if (dir == NULL){
        perror("couldn't open directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL){
        if (stat(entry->d_name, &file) == 0){
            if (file.st_size == 0){
                if (remove(entry->d_name) == 0){
                    printf("removed file");
                }else{
                    perror("couldn't remove file");
                    return 1;
                }
            }
        }else{
            perror("stat failed");
            return 1;
        }
    }
    closedir(dir);
    return 0;

}