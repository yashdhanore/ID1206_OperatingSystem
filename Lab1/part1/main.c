#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // a pipe that reads the arguments and writes the result
    int fd[2]; // fd[0] is the read end, fd[1] is the write end
    pipe(fd);  // Creating the pipe

    // fork a child process
    pid_t pid = fork();

    if (pid == 0) // child
    {
        close(fd[0]);                  // close the read end since its not used
        dup2(fd[1], STDOUT_FILENO);    // redirects stdout to the write end of the pipe
        execlp("ls", "ls", "/", NULL); // using execlp since we pass a list of arguments
    }
    else // parent
    {
        close(fd[1]);                   // close the write end since its not used
        wait(NULL);                     // wait for the child to terminate
        dup2(fd[0], STDIN_FILENO);      // redirects stdin to the read end of the pipe
        execlp("wc", "wc", "-l", NULL); // using execlp since we pass a list of arguments
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}