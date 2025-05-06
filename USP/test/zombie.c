#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if (pid == 0){
        //child process
        printf("child executing with pid : %d\n", getpid());
        // sleep(2);
        exit(0);
    }else{
        // wait(NULL);
        printf("parent executing with pid : %d\n", getpid());
        sleep(15);
        printf("parent is done sleeping");

    }

    return 0;
}