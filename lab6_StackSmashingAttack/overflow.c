#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void granted();
int checkPasswd();
int checkPasswd()
{
    char passwd[16];
    printf("Enter your passwd: ");
    gets(passwd);
    if(strcmp(passwd, "passwd1"))
    {   
        printf("\nYou fail!\n");
    }   
    else
    {   
        granted();
    }   
}
void granted(){
    printf("\nAccess granted\n");
    printf("You have gotten the privileges, and can do anything you like!! ");
    // Privileged stuff happens here.
    return ;
}
int main(){
    checkPasswd();
    return 0;
}
