#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        sleep(2); // simulate some work
        printf("Child process finished work.\n");
        exit(42); // exit with a custom code
    } else {
        // Parent process
        printf("Parent process: PID=%d, waiting for child PID=%d\n", getpid(), pid);

        // Wait for child to finish
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exited normally with code %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally.\n");
        }
    }

    return 0;
}
