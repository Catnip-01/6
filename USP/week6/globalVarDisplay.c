#include <stdio.h>
#include <stdlib.h>

extern char **environ; // Declare the global environment variable

int main() {
    char **env = environ; // Pointer to the environment variables

    // Loop through the environment variables and print each one
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
