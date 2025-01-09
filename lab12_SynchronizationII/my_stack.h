#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

// the node type in the stack
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

// the stack
typedef struct _lfstack_t {
    Node *head;
} lfstack_t;

// the push function
void lfstack_push(_Atomic lfstack_t *lfstack, int value);

// pop function
int lfstack_pop(_Atomic lfstack_t *lfstack);