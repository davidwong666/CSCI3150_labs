#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// Set it to 1 to prevent CPU reordering
#define USE_CPU_FENCE 1

/*
 * Main program
 */

sem_t beginSema1;
sem_t beginSema2;
sem_t endSema;

int X, Y;
int r1, r2;

void *thread1Func(void *param);
void *thread2Func(void *param);

int main() {
    // Initialize the semaphores
    sem_init(&beginSema1, 0, 0);
    sem_init(&beginSema2, 0, 0);
    sem_init(&endSema, 0, 0);
    int ID1 = 1;
    int ID2 = 2;
    // Spawn the threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread1Func, (void *)&ID1);
    pthread_create(&thread2, NULL, thread2Func, (void *)&ID2);

    // Repeat the experiment ad infinitum
    int detected = 0;
    for (int iterations = 1;; iterations++) {
        // Reset X and Y
        X = 0;
        Y = 0;
        // Signal both threads
        sem_post(&beginSema1);
        sem_post(&beginSema2);
        // Wait for both threads
        sem_wait(&endSema);
        sem_wait(&endSema);
        // Check if there was a simultaneous reorder
        if (r1 == 0 && r2 == 0) {
            detected++;
            printf("r1 = 0 and r2 =0: %d reorder(s) detected after %d iterations\n",
                   detected, iterations);
        }
        if (detected == 10)
            break;
    }
    return 0;
}

void *thread1Func(void *param) {
    // Endless loop
    int *ID = (int *)param;
    for (;;) {
        sem_wait(&beginSema1); // Wait for signal
        while (rand_r(ID) % 8 != 0) {
        } // Random delay
        //-------- THE TRANSACTION!-------
        X = 1;
#if USE_CPU_FENCE
        asm volatile("mfence" ::: "memory"); // Prevent CPU reordering
#else
        asm volatile("" ::: "memory"); // Prevent compiler reordering
#endif
        r1 = Y;

        sem_post(&endSema); // Notify transaction complete
    }
    return NULL; // Never returns
}

void *thread2Func(void *param) {
    int *ID = (int *)param;
    for (;;) {
        sem_wait(&beginSema2);
        while (rand_r(ID) % 8 != 0) {
        }
        // ---- THE TRANSACTION! ----

        Y = 1;
#if USE_CPU_FENCE
        asm volatile("mfence" ::: "memory");
#else
        asm volatile("" ::: "memory");
#endif
        r2 = X;

        sem_post(&endSema);
    }
    return NULL;
}