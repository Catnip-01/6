#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
// #include <

int main(){
    char *fileName = "myFile.txt";

    int n = 5;
    char buffer[n];

    int dp = open(fileName, O_RDWR);
    read(dp, buffer, n);

    int dpOut = open(fileName, O_WRONLY | O_APPEND);
    dup2(dpOut, 1);

    write(1, buffer, n);

    close(dp);
    close(dpOut);

    return 0;


}