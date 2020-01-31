#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*
 * Child to Parent Pipe, Child exec to perform Pre first.
 * Parent to perform Sort next.
 * Setup is similar to what was done in class.
 */
int main()
{
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if(pid < 0)
        exit(-1);
    else if(pid == 0)
    {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        close(fd[0]);
        execl("./pre", "./pre", (char*)0);
    }
    else
    {
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        execl("./sort", "./sort", (char*)0);
    }
    return 0;

}
