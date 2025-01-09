#include "my_new_stack.h"
#include <pthread.h>
#include <stdio.h>
_Atomic lfstack_t top = {0, NULL};

void lfstack_push(_Atomic lfstack_t *lfstack, int value) {
    lfstack_t next, orig = atomic_load(lfstack);
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    do {
        node->next = orig.head;
        next.head = node;
        next.tag = orig.tag + 1; // increase the "tag"
    } while (!atomic_compare_exchange_weak(lfstack, &orig, next));
}

int lfstack_pop(_Atomic lfstack_t *lfstack) {
    lfstack_t next, orig = atomic_load(lfstack);
    do {
        if (orig.head == NULL) {
            return -1;
        }
        next.head = orig.head->next;
        next.tag = orig.tag + 1; // increase the "tag"
    } while (!atomic_compare_exchange_weak(lfstack, &orig, next));
    printf("poping value %d\n", orig.head->data);
    free(orig.head);
    return 0;
}

void *push(void *input) {
    for (int i = 0; i < 100000; i++) {
        lfstack_push(&top, i);
        printf("push %d\n", i);
    }
    pthread_exit(NULL);
}

void *pop(void *input) {
    for (int i = 0; i < 100000;) {
        int result;
        result = lfstack_pop(&top);
        if (result == -1)
            printf("the stack is empty\n");
        else {
            i++;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[200];
    for (int i = 0; i < 100; i++)
        pthread_create(&tid[i], NULL, push, NULL);
    for (int i = 100; i < 200; i++)
        pthread_create(&tid[i], NULL, pop, NULL);
    for (int i = 0; i < 200; i++)
        pthread_join(tid[i], NULL);
    return 0;
}