#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("usage : %s <fileName>", argv[0]);
    }else{

        struct stat file;

        stat(argv[1], &file);

        if (S_ISREG(file.st_mode)) printf("regular file\n");
        if (S_ISDIR(file.st_mode)) printf("directory file\n");
        if (S_ISSOCK(file.st_mode)) printf("socket file\n");

    }

    return 0;
}