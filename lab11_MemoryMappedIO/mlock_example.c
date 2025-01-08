#include<stdio.h>
#include<sys/mman.h>

#define DATA_SIZE 2048
double buffer[DATA_SIZE];

int main(){
    if( mlock(buffer, DATA_SIZE * sizeof(double)) == -1)
        perror("mlock");
    printf("Pin the pages successfully\n");
    /*
     * Start real-time work here
     */
    if( munlock(buffer, DATA_SIZE * sizeof(double)) == -1 )
        perror("munlock");
    printf("Unpin the pages successfully\n");

    return 0;
}
