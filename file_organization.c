  GNU nano 7.2                                                         file_organization.c
#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_USERS 5

// Single-Level Directory
char singleLevel[MAX_FILES][20];
int fileCount = 0;

// Two-Level Directory
char users[MAX_USERS][20];
char twoLevel[MAX_USERS][MAX_FILES][20];
int userFileCount[MAX_USERS] = {0};
int userCount = 0;

// Function to create a file in Single-Level Directory
void createSingleLevelFile() {
    if (fileCount >= MAX_FILES) {
        printf("Directory is full!\n");
        return;
    }
    printf("Enter filename: ");
    scanf("%s", singleLevel[fileCount]);
    fileCount++;
    printf("File created successfully.\n");
}

// Function to display files in Single-Level Directory
void displaySingleLevelFiles() {
    if (fileCount == 0) {
        printf("No files in directory.\n");
        return;
    }
    printf("Files in Single-Level Directory:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s\n", singleLevel[i]);
    }
                                               [ line   1/140 ( 0%), col  1/19 (  5%), char    0/3628 ( 0%) ]
^G Help          ^O Write Out     ^W Where Is      ^K Cut           ^T Execute       ^C Location      M-U Undo         M-A Set Mark     M-] To Bracket
^X Exit          ^R Read File     ^\ Replace       ^U Paste         ^J Justify       ^/ Go To Line    M-E Redo         M-6 Copy         ^Q Where Was
