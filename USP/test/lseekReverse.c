#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("myFile.txt", O_RDONLY);
    if (fd < 0){
        perror("file opening error");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    char ch;

    while (size > 0){
        size--;
        lseek(fd, size, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);
    }

    close(fd);
    return 0;
}