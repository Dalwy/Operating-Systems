#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


/*
 * Write a small shell - called shhh - that has the
following capabilities:

1. Can execute a command with the accompanying arguments.
2. Recognize multiple pipe requests and handle them.
3. Recognize redirection requests and handle them.
4. Type "exit" to quit the shhh shell
 */

/*			Lab 2 Partial Example			*/

int main() {
    char *path, *argv[20], buf[80], n, *p;
    int m, status, inword, continu;

    while (1)
    {
        inword = 0;
        p = buf;
        m = 0;
        continu = 0;
        printf("\nshhh> ");
        while ((n = getchar()) != '\n' || continu) {
            if (n == ' ') {
                if (inword) {
                    inword = 0;
                    *p++ = 0;
                }
            } else if (n == '\n') continu = 0;
            else if (n == '\\' && !inword) continu = 1;
            else {
                if (!inword) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                } else
                    *p++ = n;
            }
        }
        *p++ = 0;
        argv[m] = 0;
        if (strcmp(argv[0], "exit") == 0) exit(0);

        /*
         * Create an array to hold the number of pipes found,
         * Create an array to hold the start of each Process.
         *
         */
        int numOfPipes = 0,
                pipes[10],
                start[10],
                startCount = 0,
                in = -1,
                out = -1,
                x;
        start[startCount++] = 0;
        for (x = 1; x < m; ++x)
        {
            if (strcmp(argv[x], "|") == 0) {
                pipes[numOfPipes++] = x;
//                printf("%d", numOfPipes);
                argv[x] = 0;
                start[startCount++] = x + 1;
            } else if (strcmp(argv[x], "<") == 0) {
                in = x + 1;
                argv[x] = 0;
                printf("%s", argv[in]);
                printf("%c", in > 0);
            } else if (strcmp(argv[x], ">") == 0) {
                out = x + 1;
                argv[x] = 0;
            }
        }
        int l_fd[2], r_fd[2], pid;
        int inputred = -1;
        int outputred = -1;
        int j;
        printf("%d", inputred);
        for (j = 0; j < numOfPipes; j++)
        {
            pid = fork();
            if (j < numOfPipes) {
                pipe(r_fd);
                printf("%s", "I made it");
            }
            if (pid < 0)
                exit(-1);
            else if (pid == 0)
            {
                printf("%s", "I made it here");
                if(in >= 0)
                {
                    inputred = open(argv[in], O_RDONLY);
                    if (inputred < 0)
                        exit(-1);
                    close(0);
                    dup(inputred);
                    close(inputred);
                }
                if (numOfPipes > 0)
                {
                    if (j == 0)
                    {
                        close(1);
                        dup(r_fd[1]);
                        close(r_fd[1]);
                        close(r_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                    } else if (j < numOfPipes)
                    {
                        close(0);
                        dup(l_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                    } else
                    {
                        // Only read from pipe
                        close(0);
                        dup(l_fd[0]);
                        close(l_fd[0]);
                        close(l_fd[1]);
                        close(r_fd[0]);
                        close(r_fd[1]);
                    }
                }
                if (j == numOfPipes && out >= 1) {

                    outputred = open(argv[out], O_CREAT | O_WRONLY, 0754);
                    if (outputred < 0)
                        exit(-1);
                    close(1);
                    dup(outputred);
                    close(outputred);
                }
                execvp(argv[start[j]], &argv[start[j]]);
                printf(" didn't exec \n ");
            }
            else if(pid > 0)
            {
                if (j > 0) {
                    close(l_fd[0]);
                    close(l_fd[1]);
                }
                l_fd[0] = r_fd[0];
                l_fd[1] = r_fd[1];
                wait(&status);
            }
        }
    }
}
