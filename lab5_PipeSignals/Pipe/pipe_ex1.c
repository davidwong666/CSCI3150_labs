/*pipe-ex1.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static int pipefd1[2], pipefd2[2];
/*Create two pipes*/
void TELL_WAIT(void)
{
  if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
}

void TELL_PARENT(void)
{
  /* send parent a message through pipe, need you to complete*/
  printf("Child send message to parent!\n");
}

void WAIT_PARENT(void)
{
  /* read message sent by parent from pipe, need you to complete*/
  printf("Child receive message from parent!\n");
}

void TELL_CHILD(void)
{
  /* send child a message through pipe, need you to complete*/
  printf("Parent send message to child!\n");
}

void WAIT_CHILD(void)
{
  /* read the message sent by child from pipe, need you to complete*/
  printf("Parent receive message from child!\n");
}

int main(int argc, char *argv[])
{
  TELL_WAIT();
  pid_t pid;
  pid = fork();
  // set a timer, process will end after 1 second.
  alarm(10);
  if (pid != 0)
  {
    while (1)
    {
      sleep(rand() % 2 + 1);
      TELL_CHILD();
      WAIT_CHILD();
    }
  }
  else
  {
    while (1)
    {
      sleep(rand() % 2 + 1);
      WAIT_PARENT();
      TELL_PARENT();
    }
  }
  return 0;
}