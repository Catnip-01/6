#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void charatatime(char *str);

int main(void)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        charatatime("output from child\n");
    }
    else
    {
        // Parent process
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char *str)
{
    char *ptr;
    int c;

    setbuf(stdout, NULL); 

    for (ptr = str; (c = *ptr++) != 0; )
    {
        putc(c, stdout);
       
    }
}
