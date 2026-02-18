#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // This is the child process
        printf("Child process: PID=%d\n", getpid());

        // Execute a new program in the child process
        execl("/bin/ls", "ls", "-l", NULL);

        // exec only returns if an error occurs
        perror("execl failed");
        exit(1);
    } else {
        // This is the parent process
        printf("Parent process: PID=%d\n", getpid());

        // Wait for the child process to finish
        wait(NULL);

        printf("Child process finished.\n");
    }

    // Exit parent process
    return 0;
}
