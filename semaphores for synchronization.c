#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>

// Define union for semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    int shmid, semid, i;
    char *shmptr;
    struct sembuf sb;

    // Create shared memory
    shmid = shmget(2041, 32, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    // Create semaphore
    semid = semget(2042, 1, 0666 | IPC_CREAT);
    if (semid < 0) {
        perror("semget");
        return 1;
    }

    // Initialize semaphore to 0 (child waits until parent signals)
    union semun arg;
    arg.val = 0;
    if (semctl(semid, 0, SETVAL, arg) < 0) {
        perror("semctl");
        return 1;
    }

    if (fork() == 0) {
        // Child process
        shmptr = shmat(shmid, 0, 0);

        // Wait (P operation)
        sb.sem_num = 0;
        sb.sem_op = -1;  // decrement
        sb.sem_flg = 0;
        semop(semid, &sb, 1);

        printf("\nCHILD PROCESS READING\n");
        for (i = 0; i < 10; i++)
            putchar(shmptr[i]);
        printf("\n");

        shmdt(shmptr);
    } else {
        // Parent process
        shmptr = shmat(shmid, 0, 0);

        printf("\nPARENT PROCESS WRITING\n");
        for (i = 0; i < 10; i++) {
            shmptr[i] = 'a' + i;
            putchar(shmptr[i]);
        }
        printf("\n");

        // Signal child (V operation)
        sb.sem_num = 0;
        sb.sem_op = 1;  // increment
        sb.sem_flg = 0;
        semop(semid, &sb, 1);

        wait(NULL);

        printf("\nPARENT PROCESS READING BACK\n");
        for (i = 0; i < 10; i++)
            putchar(shmptr[i]);
        printf("\n");

        shmdt(shmptr);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}