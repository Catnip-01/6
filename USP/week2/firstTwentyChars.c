#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    const char *fileName = "temp.txt";
    int fd = open(fileName, O_RDONLY);

    if (fd == -1){
        printf("some error whlie opening file");
        return 1;

    }

    char buffer[31];

    ssize_t bytesRead = read(fd, buffer, 30);

    if (bytesRead == 0){

        close(fd);
        printf("error while reading from file");
        return 1;
    }

    buffer[bytesRead] = '\0';

    printf("first twenty characters : %s\n", buffer);

    close(fd);

    return 0;
}