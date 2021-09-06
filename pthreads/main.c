#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <linux/types.h>

#define CHECK_NUM(x) (x == 0)

int *list_of_numbers = NULL;

/* At first is -1 so the reader knows whether to read or not */
int current_index = -1;

typedef struct {
  /* list_of_numbers mutexes */
  pthread_mutex_t list_mutex;
  pthread_mutexattr_t list_mutex_attr;

  /* current_index mutexes */
  pthread_mutex_t index_mutex;
  pthread_mutexattr_t index_mutex_attr;

  int times;
} pthread_args_t;

int init_list(size_t /*size*/);
void print_list(size_t /*size*/);
void *pthread_execute_fib(void * /*times*/);
int fib(int /*num*/);

int main(void) {
  /* Threads */
  pthread_args_t pthread_args;
  pthread_attr_t attr;
  pthread_t tid;

  printf("Enter a valid limit of numbers: ");
  scanf("%d", &pthread_args.times);

  /* Allocating the list */
  init_list(pthread_args.times);
  
  /*
   * Creation of the mutex
   *
   * This could have been done with NULL as second parameter or by assigning
   * the macro PTHREAD_MUTEX_INITIALIZER to avoid error check
   */
  pthread_mutexattr_init(&pthread_args.list_mutex_attr);
  pthread_mutex_init(&pthread_args.list_mutex, &pthread_args.list_mutex_attr);
  pthread_mutexattr_init(&pthread_args.index_mutex_attr);
  pthread_mutex_init(&pthread_args.index_mutex, &pthread_args.index_mutex_attr);

  /* Creation of the thread 
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, pthread_execute_fib, &pthread_args);
  pthread_join(tid, NULL);
  */

  pid_t pid = fork();

  if (pid > 0) {
    /* Trying to read while the son is writing */
    for (int i=0; i<pthread_args.times; i++) {
      /* Checking if it's a smart time to lock the mutex */
      pthread_mutex_lock(&pthread_args.index_mutex);
      if (current_index == -1) {
        pthread_mutex_unlock(&pthread_args.index_mutex);
        continue;
      }

      /* Locking the mutex */
      pthread_mutex_lock(&pthread_args.list_mutex);

      /* Critical Section */
      printf("Number in [%d]: %d\n", current_index, list_of_numbers[current_index]);

      /* Unlocking the mutex */
      pthread_mutex_unlock(&pthread_args.list_mutex);
      pthread_mutex_unlock(&pthread_args.index_mutex);
    }

  } else if (pid == 0) {
    pthread_execute_fib(&pthread_args);
    return 0;
  } else
    printf("Error");

  /* Printing the list */
  print_list(pthread_args.times);

  /* Cleaning my shit */
  pthread_attr_destroy(&attr);
  pthread_mutexattr_destroy(&pthread_args.list_mutex_attr);
  pthread_mutexattr_destroy(&pthread_args.index_mutex_attr);
  free(list_of_numbers);

  return 0;
}

/*
 * This is just initializing the shared 
 * list of numbers.
 */
int init_list(size_t size) {
  list_of_numbers = malloc(sizeof(int)*size);
  return (list_of_numbers == NULL);
}

void print_list(size_t size) {
  printf("List: [ ");
  for (int i=0; i<size; i++)
    printf("%d ", list_of_numbers[i]);
  printf("]\n");
}

void *pthread_execute_fib(void *pthread_args) {
  for (int i=0; i<(((pthread_args_t *)pthread_args)->times); i++) {
    /* Locking the mutexes */
    pthread_mutex_lock(&((pthread_args_t *)pthread_args)->index_mutex);
    pthread_mutex_lock(&(((pthread_args_t *)pthread_args)->list_mutex));

    /* Critical Section */
    list_of_numbers[++current_index] = fib(i);
    printf("Writing in [%d]: %d\n", current_index, list_of_numbers[current_index]);

    /* Unlocking the mutexes */
    pthread_mutex_unlock(&(((pthread_args_t *)pthread_args)->list_mutex));
    pthread_mutex_unlock(&((pthread_args_t *)pthread_args)->index_mutex);
  }

  return NULL;
}

/* Function used to calculate the fibonacci sequence */
int fib(int num) {
  if (CHECK_NUM(num) || num == 1)
    return num;

  return (fib(num-1) + fib(num-2));
}
