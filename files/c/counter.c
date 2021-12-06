#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUMCPUS     4
#define THRESHOLD   5
#define TIMESTEP    1

pthread_t tids[NUMCPUS];

typedef struct __counter_t {
  int global;
  pthread_mutex_t glock;
  int local[NUMCPUS];
  pthread_mutex_t llock[NUMCPUS];
  int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for (i = 0; i < NUMCPUS; i++){
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

typedef struct __thread_data {
  counter_t *c;
  int pid;
} thread_data;

void update(counter_t *c, int threadID, int amt) {
  int cpu = threadID % NUMCPUS;
  pthread_mutex_lock(&c->llock[cpu]);
  c->local[cpu] += amt;
  if (c->local[cpu] >= c->threshold) {
    // transfer to global (assumes amt>0)
    pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    pthread_mutex_unlock(&c->glock);
    c->local[cpu] = 0;
  }
  pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val;
}

void print_counters(counter_t *c) {
  int i;
  
  printf("0  1  2  3  | G\n");
  printf("---------------\n");
  for (i = 0; i < NUMCPUS; i++){
    printf("%d  ", c->local[i]);
  }
  printf("| %d\n\n", c->global);
}

void *thread_start(void *varg)
{
  thread_data *td = (thread_data *) varg;

  while(1){
    if (rand() % 2 == 0){
      update(td->c, td->pid, 1);
    }
    sleep(TIMESTEP);
  }
}

int main(int argc, char **argv)
{
  int threshold = 5;
  int cycle = 0;
  counter_t *c;
  int i;

  srand(time(NULL));

  c = malloc(sizeof(counter_t));
  init(c, threshold);

  for (i = 0; i < NUMCPUS; i++){
    thread_data *td;
    td = malloc(sizeof(thread_data));
    td->c = c;
    td->pid = i;
    pthread_create(&tids[i], NULL, thread_start, (void *)td);
  }

  while(1){
    printf("Cycle %d\n", cycle);
    print_counters(c);
    cycle++;
    sleep(TIMESTEP);
  }

  return 0;
}
