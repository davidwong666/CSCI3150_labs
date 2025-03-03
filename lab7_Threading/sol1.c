#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void *Allen(void *arg);
void *Bob(void *arg);

pthread_mutex_t book1;
pthread_mutex_t book2;
pthread_cond_t cv_allen_finished;
bool allen_finished;

int main()
{
  allen_finished = false;
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, &Allen, NULL);
  pthread_create(&tid2, NULL, &Bob, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}

void *Allen(void *arg)
{
  pthread_mutex_lock(&book1);
  sleep(5);
  pthread_mutex_lock(&book2);
  printf("Allen has collected all books he need, he is going to do homework!\n");
  sleep(5);
  printf("Allen has finished his homework, he has returned all books he borrowed!\n");
  pthread_mutex_unlock(&book2);
  pthread_mutex_unlock(&book1);
  allen_finished = true;
  pthread_cond_signal(&cv_allen_finished);
}

void *Bob(void *arg)
{
  pthread_mutex_lock(&book2);
  while (!allen_finished)
  {
    pthread_cond_wait(&cv_allen_finished, &book2);
  }

  printf("Bob knows he can borrow those two books now!\n");
  pthread_mutex_lock(&book1);
  sleep(5);
  printf("Bob has finished his homework now!\n");
  pthread_mutex_unlock(&book1);
  pthread_mutex_unlock(&book2);
}