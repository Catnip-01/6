#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("myFile.txt", O_RDWR);
    write(fd, "written using fd", 17);
    int dupFd = dup(fd);
    write(fd, "written using dup", 19);

    dup2(fd, STDOUT_FILENO);
    printf("this content is being redirected to myFile using dup2!");

    close(fd);
    close(dupFd);
    return 0;
}

