#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "temp.txt";  // File name to read from
    int fd = open(filename, O_RDONLY);     // Open the file in read-only mode

    if (fd == -1) {  // Check if the file failed to open
        perror("Error opening the file");  // Print an error message if opening fails
        return 1;  // Exit with an error code
    }

    // Use lseek to move the file pointer to the end of the file
    off_t file_size = lseek(fd, 0, SEEK_END);  // SEEK_END to move to the end of the file

    if (file_size == -1) {  // Check if lseek failed
        perror("Error determining file size");
        close(fd);
        return 1;
    }

    // Print the file size
    printf("File size: %ld bytes\n", file_size);

    // Close the file
    close(fd);

    return 0;
}
