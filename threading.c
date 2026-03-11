#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
void* func(void* arg) {
    // Detach the current thread from the calling thread
    pthread_detach(pthread_self());
    printf("Inside the thread\n");

    // Exit the current thread
    pthread_exit(NULL);
}

void fun() {
    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, &func, NULL);

    printf("This line may be printed before thread terminates\n");

    // Compare the two threads created
    if (pthread_equal(ptid, pthread_self()))
        printf("Threads are equal\n");
    else
        printf("Threads are not equal\n");

    // Waiting for the created thread to terminate
    pthread_join(ptid, NULL);

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

// Driver code
int main() {
    fun();
    return 0;
}
