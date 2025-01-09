#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 100000;

int filter(int *A, int *B, int *C, int a, int b, int c) {
    int i, j = 0;
    for (i = 0; i < n; ++i) {
        if (A[i] > a && B[i] > b && C[i] > c)
            j++;
    }

    return j;
}

int main() {
    srand(time(0));

    int A[100000] = {0};
    int B[100000] = {0};
    int C[100000] = {0};

    for (int i = 0; i < n; ++i) {
        int a = rand() / (RAND_MAX * 1.0) * 10;
        int b = rand() / (RAND_MAX * 1.0) * 10;
        int c = rand() / (RAND_MAX * 1.0) * 10;

        A[i] = a;
        B[i] = b;
        C[i] = c;
    }

    int filNum = filter(A, B, C, 2, 2, 2);

    printf("%d\n", filNum);

    return 0;
}