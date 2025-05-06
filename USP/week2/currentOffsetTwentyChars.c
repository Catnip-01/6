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

    char buffer[21];

    off_t nextPosition = lseek(fd, 20, SEEK_CUR);

    if (nextPosition == -1){
        printf("error while seeking 30 bits");
        return 1;
    }

    ssize_t bytesRead = read(fd, buffer, 20);

    if (bytesRead == 0){

        close(fd);
        printf("error while reading from file");
        return 1;
    }

    buffer[bytesRead] = '\0';

    printf("next twenty characters : %s\n", buffer);

    close(fd);

    return 0;
}