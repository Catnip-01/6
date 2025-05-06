#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 == 0){
        printf("pid 1 is working\n");
        sleep(2);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0){
        printf("child 2 running");
        sleep(2);
        exit(2);
    }

    waitpid(pid1, &status, 0);
    if (WIFEXITED(status)) printf("child 1 exited with status %d\n", WEXITSTATUS(status));

    wait (&status);
    if (WIFEXITED(status)){
        printf("child 2 exited with status %d", WEXITSTATUS(status));
    }

    return 0;
}