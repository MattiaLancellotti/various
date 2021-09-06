#include <pthread.h>
#include <stdio.h>

int sum; /* Dato condiviso a tutti i thread */
void *runner(void * /*param*/);

int main(int argc, char *argv[]) {
  pthread_t tid; /* Thread ID */
  pthread_attr_t attr; /* Thread attrs */

  if (argc != 2) {
    fprintf(stderr, "usage: a.out <integer value>\n");
    return -1;
  }
  if (atoi(argv[1]) < 0) {
    fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
    return -1;
  }
  
  /* reperisce gli attributi predefiniti */
  pthread_attr_init(&attr);
  /* crea il thread */
  pthread_create(&tid, &attr, runner, argv[1]);
  /* attende */
  pthread_join(tid, NULL);

  printf("sum = %d", sum);
}

void *runner(void *param) {
  int i, upper = atoi(param);
  sum = 0;

  for(i=1; i<=upper; i++)
    sum += i;

  pthread_exit(0);
}
