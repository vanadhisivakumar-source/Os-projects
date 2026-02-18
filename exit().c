#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID=%d\n", getpid());
        printf("Child is terminating using exit().\n");
        exit(5); // terminate child with exit code 5
    } else {
        // Parent process
        printf("Parent process: PID=%d, waiting for child...\n", getpid());

        wait(&status); // wait for child to finish

        if (WIFEXITED(status)) {
            printf("Child terminated normally with exit code %d\n", WEXITSTATUS(status));
        } else {
            printf("Child terminated abnormally.\n");
        }
    }

    return 0;
}
