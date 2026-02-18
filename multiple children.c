#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child_pid;
    int status;

    printf("Parent process: PID=%d\n", getpid());

    // Spawn 3 child processes
    for (int i = 0; i < 3; i++) {
        child_pid = fork();

        if (child_pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (child_pid == 0) {
            // Child process
            printf("Child %d: PID=%d\n", i, getpid());

            if (i == 0) {
                execl("/bin/echo", "echo", "Hello from child 0", NULL);
            } else if (i == 1) {
                execl("/bin/echo", "echo", "Hello from child 1", NULL);
            } else {
                execl("/bin/echo", "echo", "Hello from child 2", NULL);
            }

            perror("execl failed");
            exit(1);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < 3; i++) {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        }
    }

    printf("All children finished.\n");
    return 0;
}
