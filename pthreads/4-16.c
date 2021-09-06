#include <stdio.h>
#include <ctype.h>

#include <pthread.h>

void *thread_func(void * /*param*/);

int value = 0;

int main(void) {
  pid_t pid;

  pthread_t tid;
  pthread_attr_t attr;

  /* Generating a son */
  pid = fork();
  if (pid == 0) {
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, thread_func, NULL);
    pthread_join(tid, NULL);
    printf("CHILD: value = %d", value);
  } else if (pid > 0) {
    wait(NULL);
    printf("PARENT: value = %d", value);
  }
}

void *thread_func(void *param) {
  value = 5;
  pthread_exit(0);
}
