#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

_Atomic int count = 0;
void *adding(void *input) {
    int val;
    for (int i = 0; i < 1000000; i++) {
        do {
            val = count;
        } while (!atomic_compare_exchange_weak(&count, &val, val + 1));
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