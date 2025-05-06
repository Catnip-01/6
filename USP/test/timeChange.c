#include <stdio.h>
#include <sys/stat.h>
#include <utime.h>

int main(){
    struct stat file;
    struct utimbuf newTimes;

    stat("myFile.txt", &file);

    newTimes.actime = file.st_atime;
    newTimes.modtime = file.st_mtime;

    utime("timeFile.txt", &newTimes);

    return 0;
}