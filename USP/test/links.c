#include <stdio.h>
#include <unistd.h>

int main(){
    if (link("myFile.txt", "hard.txt") == 0){
        printf("hard link successful");

    }else{
        perror("hard link failed");
        return 1;
    }

    if (symlink("myFile.txt", "soft.txt") == 0){
        printf("soft link successful");

    }else{
        perror("soft link failed");
        return 1;
    }
    return 0;
}