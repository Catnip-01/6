#include <fcntl.h>     // For open(), O_RDONLY, O_WRONLY, O_APPEND
#include <unistd.h>    // For read(), write(), dup3(), close()
#include <stdio.h>     // For perror()

int main() {
    const char *filename = "temp.txt";  // Name of the file
    int fd = open(filename, O_RDONLY);     // Open the file in read-only mode

    if (fd == -1) {  // Check if the file opened successfully
        perror("Error opening the file");  // Print error message if opening fails
        return 1;  // Exit with an error code
    }

    // Buffer to store the n characters to be read and appended
    char buffer[21];  // Read 20 chars + 1 for null terminator

    // Read n (20 in this case) characters from the file
    ssize_t bytesRead = read(fd, buffer, 20);

    if (bytesRead == -1) {  // Check if reading failed
        perror("Error reading the file");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';  // Null-terminate the string

    // Duplicate the file descriptor for appending to the file
    int fd_append = open(filename, O_WRONLY | O_APPEND);  // Open for appending
    if (fd_append == -1) {
        perror("Error opening the file for appending");
        close(fd);
        return 1;
    }

    // Use dup3() to duplicate the original file descriptor to append
    if (dup2(fd_append, fd) == -1) {  // Set fd to append mode
        perror("Error duplicating the file descriptor");
        close(fd);
        close(fd_append);
        return 1;
    }

    // Write the read characters to the file (appending)
    ssize_t bytesWritten = write(fd, buffer, bytesRead);
    if (bytesWritten == -1) {
        perror("Error writing to the file");
        close(fd);
        close(fd_append);
        return 1;
    }

    printf("Appended the following to the file: %s\n", buffer);

    // Close the file descriptors
    close(fd);
    close(fd_append);

    return 0;  // Exit successfully
}
