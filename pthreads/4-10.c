#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10

int sum; /* Dato condiviso a tutti i thread */
void *runner(void * /*param*/);

int main(int argc, char *argv[]) {
  pthread_t workers[NUM_THREADS]; /* Thread ID */
  pthread_attr_t attrs[NUM_THREADS]; /* Thread attrs */

  if (argc != 2) {
    fprintf(stderr, "usage: a.out <integer value>\n");
    return -1;
  }
  if (atoi(argv[1]) < 0) {
    fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
    return -1;
  }
  
  for (int i=0; i<NUM_THREADS; i++) {
    /* reperisce gli attributi predefiniti */
    pthread_attr_init(attrs+i);

    /* crea il thread */
    pthread_create(workers+i, attrs+i, runner, argv[1]);

    /* attende */
    pthread_join(workers[i], NULL);
  }

  printf("sum = %d", sum);
}

void *runner(void *param) {
  int i, upper = atoi(param);
  sum = 0;

  for(i=1; i<=upper; i++)
    sum += i;

  pthread_exit(0);
}
