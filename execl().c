#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Before execl: PID=%d\n", getpid());

    // Replace current process with /bin/ls
    execl("/bin/ls", "ls", "-l", NULL);

    // If execl fails, this line will execute
    perror("execl failed");
    exit(1);
}
