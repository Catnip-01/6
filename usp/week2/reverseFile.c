#include <fcntl.h>     // For open(), O_RDONLY
#include <unistd.h>    // For lseek(), read(), close()
#include <stdio.h>     // For perror(), printf()

int main() {
    const char *filename = "temp.txt";  // Name of the file
    int fd = open(filename, O_RDONLY);     // Open the file in read-only mode

    if (fd == -1) {  // Check if the file opened successfully
        perror("Error opening the file");  // Print error message if opening fails
        return 1;  // Exit with an error code
    }

    // Get the size of the file by moving the file pointer to the end
    off_t file_size = lseek(fd, 0, SEEK_END);

    if (file_size == -1) {  // Check if lseek failed
        perror("Error determining file size");
        close(fd);
        return 1;
    }

    // Read the file backwards by moving the file pointer to the end and then reading byte-by-byte
    char ch;
    for (off_t i = file_size - 1; i >= 0; i--) {  // Loop from last byte to first
        // Move the file pointer to position 'i'
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("Error seeking the file");
            close(fd);
            return 1;
        }

        // Read one byte from the current position
        if (read(fd, &ch, 1) == -1) {
            perror("Error reading the file");
            close(fd);
            return 1;
        }

        // Print the byte to the standard output (console)
        write(STDOUT_FILENO, &ch, 1);  // Using write() to output the byte
    }

    // Close the file after use
    close(fd);

    return 0;  // Exit the program successfully
}
