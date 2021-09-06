#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CHECK_NUM(x) (x == 0)

int *list_of_numbers = NULL;

int init_list(size_t /*size*/);
void print_list(size_t /*size*/);
void *pthread_execute_fib(void * /*times*/);
int fib(int /*num*/);

int main(void) {
  int lim;

  /* Threads */
  pthread_attr_t attr;
  pthread_t tid;

  printf("Enter a valid limit of numbers: ");
  scanf("%d", &lim);

  /* Allocating the list */
  init_list(lim);
  
  /* Creation of the thread */
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, pthread_execute_fib, &lim);
  pthread_join(tid, NULL);

  print_list(lim);

  free(list_of_numbers);
  return 0;
}

int init_list(size_t size) {
  list_of_numbers = malloc(sizeof(int)*size);
  return (list_of_numbers == NULL);
}

void print_list(size_t size) {
  printf("List: [ ");
  for (int i=0; i<size; i++)
    printf("%d ", list_of_numbers[i]);
  printf("]");
}

void *pthread_execute_fib(void *times) {
  int j=0;

  for (int i=0; i<*(int *)times; i++)
    list_of_numbers[j++] = fib(i);

  return NULL;
}

int fib(int num) {
  if (CHECK_NUM(num) || num == 1)
    return num;

  return (fib(num-1) + fib(num-2));
}
