#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREADS 100
#define MAX_SLEEP 10
#define MAX_PID 5000
#define MIN_PID 300

#define EXIT(x, y) if (!x) return y;
#define ERROR(condition, y, msg) if (!condition) { \
                                  fprintf(stderr, "%s", msg); \
                                  return y; }

enum { ALLOCATION_FAILED=0, ALLOCATION_SUCCESSFUL };

struct pthread_args {
  int pid;
  int time;
};

int allocate_map(void);
int allocate_pid(void);
void release_pid(int /* pid */);
void *pthread_release_pid(void * /* pthread_args_p */);

static char *pid_list = NULL;

int main(void) {
  struct pthread_args args[MAX_THREADS];

  pthread_attr_t attrs[MAX_THREADS];
  pthread_t tids[MAX_THREADS];

  srand((unsigned) time(NULL));

  /* creating a pool of pids */
  ERROR(allocate_map(), 1, "Allocation failed");

  /* initializing the threads */
  for (int i=0; i<MAX_THREADS; i++) {
    args[i].pid = allocate_pid();
    args[i].time = rand() % MAX_SLEEP;

    pthread_attr_init(attrs+i);
    pthread_create(tids+i, attrs+i, pthread_release_pid, (void *)&args[i]);
  }

  for (int i=0; i<MAX_THREADS; i++) {
    /* waiting for the thread */
    pthread_join(tids[i], NULL);

    /* releasing the pids */
    printf("thread[%d] has finished\n", args[i].pid);
    release_pid(args[i].pid);
  }

  return 0;
}

int allocate_map(void) {
  pid_list = malloc(sizeof(char)*(MAX_PID-MIN_PID));

  return pid_list ? ALLOCATION_SUCCESSFUL : ALLOCATION_FAILED;
}

int allocate_pid(void) {
  EXIT(pid_list, -1)

  for (size_t i=0; i<(MAX_PID-MIN_PID); i++)
    if (!pid_list[i]) {
      pid_list[i] = 1;
      return i+300;
    }

  return -1;
}

void release_pid(int pid) {
  EXIT(pid_list,)
  pid_list[pid-300] = 0;
}

void *pthread_release_pid(void *pthread_args_p) {
  printf("pthread_pid  = %d - ", ((struct pthread_args *)pthread_args_p)->pid);
  printf("pthread_time = %d\n", ((struct pthread_args *)pthread_args_p)->time);

  /* sleeping zzzz.. */
  sleep(((struct pthread_args *)pthread_args_p)->time);

  return (void *)(&((struct pthread_args *)pthread_args_p)->pid);
}
