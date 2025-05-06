#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    const char *fileName = "temp.txt";

    int fd = creat(fileName, 0644);

    if (fd == -1){
        printf("error opening file");
        return 1;
    }

    printf("file created successfully with descriptor : %d", fd);

    close(fd);
    
    return 0;


}