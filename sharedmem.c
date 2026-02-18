#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int shmid, i;
    char *shmptr;

    // Create shared memory
    shmid = shmget(2041, 32, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    if (fork() == 0) {
        // Child process
        shmptr = shmat(shmid, 0, 0);
        printf("\nCHILD PROCESS READING\n");
        for (i = 0; i < 10; i++)
            putchar(shmptr[i]);   // child just reads
        printf("\n");
        shmdt(shmptr);
    } else {
        // Parent process
        shmptr = shmat(shmid, 0, 0);
        printf("\nPARENT PROCESS WRITING\n");
        for (i = 0; i < 10; i++) {
            shmptr[i] = 'a' + i;  // write a..j
            putchar(shmptr[i]);
        }
        printf("\n");
        wait(NULL);

        printf("\nPARENT PROCESS READING BACK\n");
        for (i = 0; i < 10; i++)
            putchar(shmptr[i]);   // still a..j
        printf("\n");

        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}