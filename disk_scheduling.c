#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 50

// Function to calculate the total seek time in FCFS
void fcfs(int requests[], int n, int head) {
    int seekTime = 0;
    printf("\nFCFS Disk Scheduling:\n");
    for (int i = 0; i < n; i++) {
        seekTime += abs(requests[i] - head);
        head = requests[i];
    }
    printf("Total seek time: %d\n", seekTime);
}

// Function to calculate the total seek time in SCAN
void scan(int requests[], int n, int head, int diskSize) {
    int seekTime = 0;
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftIndex = 0, rightIndex = 0;

    // Divide requests into left and right of the head
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[leftIndex++] = requests[i];
        } else {
            right[rightIndex++] = requests[i];
        }
    }

    // Sort left (descending) and right (ascending)
    for (int i = 0; i < leftIndex - 1; i++) {
        for (int j = i + 1; j < leftIndex; j++) {
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < rightIndex - 1; i++) {
        for (int j = i + 1; j < rightIndex; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    // Move left then right
    seekTime += abs(head - left[0]);
    for (int i = 0; i < leftIndex - 1; i++) {
        seekTime += abs(left[i] - left[i + 1]);
    }
    seekTime += abs(left[leftIndex - 1] - right[0]);
    for (int i = 0; i < rightIndex - 1; i++) {
        seekTime += abs(right[i] - right[i + 1]);
    }

    printf("\nSCAN Disk Scheduling:\n");
    printf("Total seek time: %d\n", seekTime);
}

// Function to calculate the total seek time in C-SCAN
void cscan(int requests[], int n, int head, int diskSize) {
    int seekTime = 0;
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftIndex = 0, rightIndex = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[leftIndex++] = requests[i];
        } else {
            right[rightIndex++] = requests[i];
        }
    }

    // Sort left (descending) and right (ascending)
    for (int i = 0; i < leftIndex - 1; i++) {
        for (int j = i + 1; j < leftIndex; j++) {
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < rightIndex - 1; i++) {
        for (int j = i + 1; j < rightIndex; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    // Move to right end, wrap around, then left
    seekTime += (diskSize - 1) - head;
    seekTime += (diskSize - 1);
    seekTime += right[0];
    for (int i = 0; i < rightIndex - 1; i++) {
        seekTime += abs(right[i] - right[i + 1]);
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Total seek time: %d\n", seekTime);
}

// Function to calculate the total seek time in LOOK
void look(int requests[], int n, int head) {
    int seekTime = 0;
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftIndex = 0, rightIndex = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[leftIndex++] = requests[i];
        } else {
            right[rightIndex++] = requests[i];
        }
    }

    // Sort left (descending) and right (ascending)
    for (int i = 0; i < leftIndex - 1; i++) {
        for (int j = i + 1; j < leftIndex; j++) {
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < rightIndex - 1; i++) {
        for (int j = i + 1; j < rightIndex; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    // Move left then right
    seekTime += abs(head - left[0]);
    for (int i = 0; i < leftIndex - 1; i++) {
        seekTime += abs(left[i] - left[i + 1]);
    }
    seekTime += abs(left[leftIndex - 1] - right[0]);
    for (int i = 0; i < rightIndex - 1; i++) {
        seekTime += abs(right[i] - right[i + 1]);
    }

    printf("\nLOOK Disk Scheduling:\n");
    printf("Total seek time: %d\n", seekTime);
}

// Function to calculate the total seek time in C-LOOK
void clook(int requests[], int n, int head) {
    int seekTime = 0;
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int leftIndex = 0, rightIndex = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[leftIndex++] = requests[i];
        } else {
            right[rightIndex++] = requests[i];
        }
    }

    // Sort left (descending) and right (ascending)
    for (int i = 0; i < leftIndex - 1; i++) {
        for (int j = i + 1; j < leftIndex; j++) {
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < rightIndex - 1; i++) {
        for (int j = i + 1; j < rightIndex; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }

    // Move right then wrap to left
    seekTime += abs(head - right[0]);
    for (int i = 0; i < rightIndex - 1; i++) {
        seekTime += abs(right[i] - right[i + 1]);
    }
    seekTime += abs(right[rightIndex - 1] - left[0]);
    for (int i = 0; i < leftIndex - 1; i++) {
        seekTime += abs(left[i] - left[i + 1]);
    }

    printf("\nC-LOOK Disk Scheduling:\n");
    printf("Total seek time: %d\n", seekTime);
}

// Main function
int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;
    int diskSize = 200;

    fcfs(requests, n, head);
    scan(requests, n, head, diskSize);
    cscan(requests, n, head, diskSize);
    look(requests, n, head);
    clook(requests, n, head);

    return 0;
}
