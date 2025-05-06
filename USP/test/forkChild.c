#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int fd = open("myFile.txt", O_RDONLY);
    if (fd < 0){
        perror("error while opening the file!");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0){
        perror("fork failed");
        return 1;
    }
    char ch;
    read(fd, &ch, 1);
    printf("both parent and child try to read : %c\n", ch);

    if (pid == 0){
        //child process
        //in the child process you are required to read some value
        //read val using read, store in char, and print it.
        
        read(fd, &ch, 1);
        printf("child reads : %c\n", ch);


    }else{
        //parent process
        wait(NULL);        
        read(fd, &ch, 1);
        printf("parent reads : %c\n", ch);
    }

    close(fd);
    return 0;
}