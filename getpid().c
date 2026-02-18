#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        // Wait for child to finish
        wait(NULL);
        printf("Child process finished.\n");
    }

    return 0;
}
