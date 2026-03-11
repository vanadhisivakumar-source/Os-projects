#include <stdio.h>

int main() {
    int memsize = 15;          // Total memory size
    int pagesize, nofpage;     // Page size and number of pages
    int p[100];                // Page table storing frame numbers
    int frameno, offset;       // Frame number and offset
    int logadd, phyadd;        // Logical and physical addresses
    int i;
    int choice = 0;

    printf("Memory size is %d\n", memsize);

    // Input page size
    printf("Enter page size: ");
    scanf("%d", &pagesize);

    // Validate page size
    if (pagesize <= 0 || pagesize > memsize) {
        printf("Invalid page size! Must be between 1 and %d.\n", memsize);
        return 1;
    }

    // Calculate the number of pages
    nofpage = memsize / pagesize;
    printf("Number of pages: %d\n", nofpage);

    // Input frame numbers for each page
    for (i = 0; i < nofpage; i++) {
        printf("Enter the frame number for page %d: ", i);
        scanf("%d", &p[i]);
        // Validate frame number
        if (p[i] < 0) {
            printf("Invalid frame number! Must be non-negative.\n");
            return 1;
        }
    }

    // Logical to physical address translation loop
    do {
        printf("Enter a logical address: ");
        scanf("%d", &logadd);

        // Validate logical address
        if (logadd < 0 || logadd >= memsize) {
            printf("Invalid logical address! Must be between 0 and %d.\n", memsize - 1);
            continue;
        }

        frameno = logadd / pagesize;             // Find page number
        offset = logadd % pagesize;              // Find offset
        phyadd = (p[frameno] * pagesize) + offset; // Calculate physical address

        printf("Physical address is: %d\n", phyadd);

        printf("Do you want to continue (1 for Yes, 0 for No)?: ");
        scanf("%d", &choice);

    } while (choice == 1);

    return 0;
}
