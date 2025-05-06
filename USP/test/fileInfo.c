#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("myFile.txt", O_RDONLY);
    struct stat file;

    int ans = stat("myFile.txt", &file);

    if (ans < 0){
        perror("issue while using the stat function");
        return 1;
    }

    printf("file size : %ld\n", file.st_size);
    printf("file permissions : %o\n", file.st_mode);
    printf("number of links : %ld\n", file.st_nlink);
    printf("inode value : %ld\n", file.st_ino);
    // printf("file size : %ld\n", file.st_size);
    close(fd);
    return 0;
}