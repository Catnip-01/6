//code to demonstrate open with all parameters

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    const char *fileName = "temp.txt";

    int fd = open(fileName, O_WRONLY | O_CREAT, 0644);

    if (fd == -1){
        printf("error opening file");
        return 1;

    }

    printf("file opened successfully with descriptor : %d\n", fd);

    close(fd);

    return 0;
}