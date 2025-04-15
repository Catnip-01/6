#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

/* Helper function to print exit status */
void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",
               WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

void err_sys(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(void)
{
    pid_t pid;
    int status;

    /* First child process exits normally */
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) 
        exit(7); /* Child exits with status 7 */

    if (wait(&status) != pid) 
        err_sys("wait error");
    pr_exit(status); /* Print child exit status */

    /* Second child process aborts */
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) 
        abort(); /* Generates SIGABRT */

    if (wait(&status) != pid) 
        err_sys("wait error");
    pr_exit(status); /* Print child exit status */

    /* Third child causes a floating-point exception */
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0; /* Divide by zero generates SIGFPE */

    if (wait(&status) != pid) 
        err_sys("wait error");
    pr_exit(status); /* Print child exit status */

    exit(0);
}
