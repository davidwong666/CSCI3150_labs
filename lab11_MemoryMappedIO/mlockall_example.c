#include<stdio.h>
#include<sys/mman.h>
#define SIZE 500

struct record {
    char name[128];
    int count;
    unsigned char dummy_array[1024000];
    struct record * next;
};

int main(void){
    struct record * a[SIZE];
    int i;
    printf("Starting mlockall_example.\n");
    /* 
     * Reallocate memory required by the application before
     * real-time processing begins
     */
    /* Insert code here */

    /* Pin all pages mapped to the process in memory */
    printf("Pin all the pages in memory.\n");
    if(mlockall(MCL_CURRENT | MCL_FUTURE) < 0) {
        perror("mlockall");
        return 1;
    }
    /*
     * Begin real-time processing 
     */

    /*
     * Release all memory belonging to this process 
     */
    printf("Finished, clean up.\n");
    munlockall();
    return 0;
}
