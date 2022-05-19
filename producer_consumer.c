#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void);
void *consumer(void);

int *buffer;
int limit = 0, f = 0;

int main(void) 
{
  int producers = 0, consumers = 0, size = 0, i = 0;
  scanf(" %d %d %d %d", &producers, &consumers, &limit, &size);

  sem_init(&empty, 0, size);
  sem_init(&full, 0, 0);
  pthread_mutex_init(&mutex, NULL);
  pthread_t t_consumers[consumers];
  pthread_t t_producers[producers];
  buffer = (int*) malloc(size *sizeof(int));

  for (i = 0; i < producers; i++) {
    pthread_create(&t_producers[i], NULL, &producer, NULL);
  }
  for (i = 0; i < consumers; i++) {
    pthread_create(&t_consumers[i], NULL, &consumer, NULL);
  }

  for (i = 0; i < consumer; i++) {
    pthread_join(t_consumers[i], NULL);
  }
  for (i = 0; i < producers; i++) {
    pthread_join(t_producers[i], NULL);
  }

  sem_destroy(&empty);
  sem_destroy(&full);
  pthread_mutex_destroy(&mutex);

  return 0;
}

void *producer(void)
{
  int x = 0, aux = 0;

  while (1) {
    aux = x*2 + 1;

    sem_wait(&empty);

    pthread_mutex_lock(&mutex);
    buffer[f] = aux;
    printf("\nProdutor produzindo %d na posicao %d\n", aux, f);
    x++;
    f++;
    pthread_mutex_unlock(&mutex);
    if (x == limit) {
      x = 0;
    }

    sem_post(&full);
  }
}

void *consumer(void)
{
  while (1) {
    sem_wait(&full);

    pthread_mutex_lock(&mutex);
    int aux = buffer[f-1];
    printf("\nConsumidor consumindo %d da posicao %d\n", aux, f-1);
    f--;
    pthread_mutex_unlock(&mutex);

    sem_post(empty);
  }
}