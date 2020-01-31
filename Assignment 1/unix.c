#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * Take a UNIX Command from the command line and fork() a child ot execute it.
 * child process is executing the command.
 * Parent process waits for termination of the child process.
 * Child PID and Parent PID get printed.
 */
int main(int argc, char* argv[])
{
    int x;
    int pid;
    pid = fork();
    for(x = 0; x < argc - 1; x++)
        strcpy(argv[x], argv[x+1]);

    argv[argc-1] = (char*)0;
    if(pid < 0)
        exit(0);
    else if(pid == 0)
    {
        printf("PID: %d\nPPID: %d\n", getpid(), getppid());
        execvp(argv[0], &argv[1]);
    }
    else
        wait(0);

    return 0;
}