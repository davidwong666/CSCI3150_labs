#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

int count = 0;
_Atomic int lock = 0;
void *adding(void *input) {
    int expected = 0;
    for (int i = 0; i < 1000000; i++) {
        while (!atomic_compare_exchange_weak(
            &lock, &expected, 1)) // if the lock is 0(unlock), then set it to 1(lock)
            expected = 0; // if the CAS fails, the expected will be set to 1, so we need
                          // to change it to 0 again.
        count++;
        lock = 0;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[10];
    for (int i = 0; i < 10; i++)
        pthread_create(&tid[i], NULL, adding, NULL);
    for (int i = 0; i < 10; i++)
        pthread_join(tid[i], NULL);
    printf("the value of count is %d\n", count);
}