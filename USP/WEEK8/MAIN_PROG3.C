#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

void create_daemon() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS); // Parent exits
    }

    // Child becomes the session leader
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // Set file mode creation mask to 0
    umask(0);

    // Change the current working directory to the root directory
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirect standard file descriptors to /dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);
}

int main() {
    create_daemon();
    openlog("daemon_ex", LOG_PID, LOG_DAEMON);

    while (1) {
        syslog(LOG_NOTICE, "Daemon is running...\n");
        sleep(30);
    }

    closelog();
    return EXIT_SUCCESS;
}