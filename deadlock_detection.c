#include <stdio.h>

int main() {
    int tp, tr;
    int alloc[10][10], max[10][10];
    int avail[10], work[10], finish[10];
    int safeSeq[10];
    int i, j, k, count = 0;

    printf("Enter total no of processes: ");
    scanf("%d", &tp);

    printf("Enter total no of resources: ");
    scanf("%d", &tr);

    printf("Enter claim (Max. Need) matrix\n");
    for (i = 0; i < tp; i++) {
        printf("Process %d:\n", i + 1);
        for (j = 0; j < tr; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter allocation matrix\n");
    for (i = 0; i < tp; i++) {
        printf("Process %d:\n", i + 1);
        for (j = 0; j < tr; j++)
            scanf("%d", &alloc[i][j]);
    }

    printf("Enter availability vector (available resources):\n");
    for (i = 0; i < tr; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    for (i = 0; i < tp; i++)
        finish[i] = 0;

    // Banker's style safety check
    while (count < tp) {
        int found = 0;
        for (i = 0; i < tp; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (j = 0; j < tr; j++) {
                    if (max[i][j] - alloc[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (j = 0; j < tr; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break; // no process could run in this pass
    }

    if (count == tp) {
        printf("\nNo deadlock detected.\n");
        printf("Safe sequence is: ");
        for (i = 0; i < tp; i++)
            printf("P%d ", safeSeq[i] + 1);
        printf("\n");
    } else {
        printf("\nDeadlock detected!\n");
        printf("Deadlock causing processes are: ");
        for (i = 0; i < tp; i++) {
            if (!finish[i])
                printf("P%d ", i + 1);
        }
        printf("\n");
    }

    return 0;
}
