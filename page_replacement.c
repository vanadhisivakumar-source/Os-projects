  GNU nano 7.2                                                         page_replacement.c
#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_REFERENCES 100

int frames[MAX_FRAMES];   // Page frames
int freq[MAX_FRAMES];     // Frequency array for LFU
int time[MAX_FRAMES];     // Time array for LRU
int pageFaults = 0, frameCount, referenceCount;

// Initialize frames to -1 (empty)
void initFrames() {
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }
    pageFaults = 0;
}

// Check if a page exists in the frames, return its index or -1
int findPage(int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

// Display current state of frames
void displayFrames() {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
                                                                     [ Read 146 lines ]
^G Help          ^O Write Out     ^W Where Is      ^K Cut           ^T Execute       ^C Location      M-U Undo         M-A Set Mark     M-] To Bracket
^X Exit          ^R Read File     ^\ Replace       ^U Paste         ^J Justify       ^/ Go To Line    M-E Redo         M-6 Copy         ^Q Where Was
