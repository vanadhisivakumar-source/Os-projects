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
        execl("/bin/echo", "echo", "Hello from the child process!", NULL);

        // If execl fails
        perror("execl failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        // Wait for child to finish
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally.\n");
        }
    }

    return 0;
}
