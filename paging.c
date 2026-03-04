// C program to implement simple paging technique

#include <stdio.h>

int main() {
    int memSize, pageSize, numPages;
    int frame[50];   // frame numbers for each page
    int i, logicalAddr, pageNum, offset, physAddr;
    int cont = 1;

    // Input memory size and page size
    printf("Memory size is: ");
    scanf("%d", &memSize);

    printf("Enter page size: ");
    scanf("%d", &pageSize);

    // Calculate number of pages
    numPages = memSize / pageSize;
    printf("Number of pages: %d\n", numPages);

    // Input frame numbers for each page
    for (i = 0; i < numPages; i++) {
        printf("Enter the frame number for page %d: ", i);
        scanf("%d", &frame[i]);
    }

    // Address translation loop
    while (cont) {
        printf("Enter a logical address: ");
        scanf("%d", &logicalAddr);

        pageNum = logicalAddr / pageSize;
        offset = logicalAddr % pageSize;

        if (pageNum >= numPages) {
            printf("Invalid logical address! Page number out of range.\n");
        } else {
            physAddr = frame[pageNum] * pageSize + offset;
            printf("Physical address is: %d\n", physAddr);
        }

        printf("Do you want to continue (1 for Yes, 0 for No)?: ");
        scanf("%d", &cont);
    }

    return 0;
}
