#include <stdio.h>
#include <stdlib.h>

int main() {
    int found, flag, l, tp, tr;
    int p[10][10], c[10][10], m[10], r[10], a[10], temp[10];
    int i, j, k = 1, sum = 0;

    printf("Enter total no of processes: ");
    scanf("%d", &tp);

    printf("Enter total no of resources: ");
    scanf("%d", &tr);

    printf("Enter claim (Max Need) matrix:\n");
    for (i = 0; i < tp; i++) {
        printf("Process %d:\n", i);
        for (j = 0; j < tr; j++)
            scanf("%d", &c[i][j]);
    }

    printf("Enter allocation matrix:\n");
    for (i = 0; i < tp; i++) {
        printf("Process %d:\n", i);
        for (j = 0; j < tr; j++)
            scanf("%d", &p[i][j]);
    }

    printf("Enter resource vector (Total resources):\n");
    for (i = 0; i < tr; i++)
        scanf("%d", &r[i]);

    printf("Enter availability vector (Available resources):\n");
    for (i = 0; i < tr; i++) {
        scanf("%d", &a[i]);
        temp[i] = a[i];
    }

    // Find processes with zero allocation
    for (i = 0; i < tp; i++) {
        sum = 0;
        for (j = 0; j < tr; j++)
            sum += p[i][j];
        if (sum == 0) {
            m[k] = i;
            k++;
        }
    }

    // Deadlock detection
    for (i = 0; i < tp; i++) {
        for (l = 1; l < k; l++) {
            if (i != m[l]) {
                flag = 1;
                for (j = 0; j < tr; j++) {
                    if (c[i][j] > temp[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    m[k] = i;
                    k++;
                    for (j = 0; j < tr; j++)
                        temp[j] += p[i][j];
                }
            }
        }
    }

    printf("\nDeadlock causing processes are: ");
    for (j = 0; j < tp; j++) {
        found = 0;
        for (i = 1; i < k; i++) {
            if (j == m[i])
                found = 1;
        }
        if (found == 0)
            printf("P%d\t", j);
    }
    printf("\n");

    return 0;
}
