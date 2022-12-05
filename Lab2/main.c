#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int buffer = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment()
{
    void *counter = 0;

    // to make sure that the buffer is not accessed by more than one thread at a time and
    // buffer is less than 15
    while (pthread_mutex_lock(&mutex) || buffer < 15)
    {
        printf("TID: %lu, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer++);

        // counting the number of times the buffer is incremented by the thread
        counter++;

        // unlocking when critical section is done
        pthread_mutex_unlock(&mutex);

        // microsecond sleep to get fair distribution of buffer access
        usleep(0.1);
    }

    pthread_mutex_unlock(&mutex);

    // returning the number of times the buffer is incremented by the thread
    return (void *)counter;
}

int main()
{
    // initializing threads
    pthread_t thread1, thread2, thread3;

    // counter for each thread
    int thread1_count;
    int thread2_count;
    int thread3_count;

    pthread_mutex_init(&mutex, NULL);

    // creating threads, succesful creation returns 0
    if (pthread_create(&thread1, NULL, &increment, NULL) != 0)
        printf("Error creating thread 1");
    if (pthread_create(&thread2, NULL, &increment, NULL) != 0)
        printf("Error creating thread 2");
    if (pthread_create(&thread3, NULL, &increment, NULL) != 0)
        printf("Error creating thread 3");

    // joining threads, succesful join returns 0
    if (pthread_join(thread1, (void **)&thread1_count) != 0)
        printf("Error joining thread 1");
    if (pthread_join(thread2, (void **)&thread2_count) != 0)
        printf("Error joining thread 2");
    if (pthread_join(thread3, (void **)&thread3_count) != 0)
        printf("Error joining thread 3");

    printf("TID %lu worked on the buffer %d times\n", thread1, thread1_count);
    printf("TID %lu worked on the buffer %d times\n", thread2, thread2_count);
    printf("TID %lu worked on the buffer %d times\n", thread3, thread3_count);

    printf("Total buffer accesses: %d\n", buffer);

    // terminating threads, prevents segmenation fault
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}