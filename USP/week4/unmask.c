#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    mode_t old_mask = umask(0077); // Set umask, save original
    int fd = open("file1.txt", O_CREAT | O_WRONLY, 0666); // Create file
    if (fd != -1) {
        write(fd, "Hello\n", 6);
        close(fd);
        printf("File created.\n");
    } else {
        printf("File creation failed.\n");
    }
    umask(old_mask); // Restore original umask
    return 0;
}