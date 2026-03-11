  GNU nano 7.2                                                          file_allocation.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

int memory[MAX_BLOCKS] = {0}; // 0 means free, 1 means allocated

// Structure for Indexed and Linked Allocation
typedef struct {
    int indexBlock;
    int blocks[MAX_BLOCKS];
    int blockCount;
} IndexedFile;

typedef struct {
    int startBlock;
    int blocks[MAX_BLOCKS];
    int blockCount;
} LinkedFile;

// Sequential Allocation
void sequentialAllocation(int start, int size) {
    int i, freeCount = 0;
    // Check if sufficient space is available
    for (i = start; i < start + size; i++) {
        if (memory[i] == 0) freeCount++;
    }
    if (freeCount == size) {
        for (i = start; i < start + size; i++) memory[i] = 1;
        printf("File allocated from block %d to %d.\n", start, start + size - 1);
    } else {
        printf("Not enough contiguous free space available!\n");
    }
}

// Indexed Allocation
void indexedAllocation(IndexedFile *file) {
    printf("Enter index block: ");
                                               [ line   1/126 ( 0%), col  1/19 (  5%), char    0/3667 ( 0%) ]
^G Help          ^O Write Out     ^W Where Is      ^K Cut           ^T Execute       ^C Location      M-U Undo         M-A Set Mark     M-] To Bracket
^X Exit          ^R Read File     ^\ Replace       ^U Paste         ^J Justify       ^/ Go To Line    M-E Redo         M-6 Copy         ^Q Where Was
