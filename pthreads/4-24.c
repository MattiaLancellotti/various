#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CHECK_DIV(x, y) !(x % y)
#define CHECK_NUM(x, y) (x == y)

int *array_of_primes = NULL;
int new_size = 0;

enum state { NOT_PRIME, PRIME, NOT_ACCEPTABLE };

int init_array(size_t /*size*/);
void *thread_find_primes(void * /*curr*/);
void *thread_list_numbers(void * /*list*/);
enum state divide(int /*num*/, int /*div*/);
void print_array(size_t /*size*/);

int main(int argc, char *argv[]) {
  int num;

  /* Thread */
  pthread_attr_t attr;
  pthread_t tid;

  /* Taking input */
  printf("Enter a valid positive number: ");
  scanf("%d", &num);

  /* Checks and memory allocation*/
  init_array(num);
  num = (CHECK_DIV(num, 2) ? num-1 : num);

  /* Creating thread */
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, thread_find_primes, &num);
  pthread_join(tid, NULL);

  /* printing the array */
  print_array(CHECK_NUM(new_size, 0) ? num : new_size);

  if (array_of_primes)
    free(array_of_primes);

  return 0;
}

int init_array(size_t size) {
  array_of_primes = malloc(sizeof(int) * size);
  return array_of_primes == NULL;
}

void *thread_find_primes(void *curr) {
  int num = *((int *)curr);
  int i;

  if (num <= 0)
    return NULL;
  
  for (i=0; num; num--)
    if (divide(num, num-1) == PRIME)
      array_of_primes[i++] = num;

  new_size = i;
}

enum state divide(int num, int div) {
  if (div <= 1)   //exit condition
    return PRIME;
  
  if (CHECK_DIV(num, div))
    return NOT_PRIME;
  else
    return divide(num, div-1);
}

void print_array(size_t size) {
  printf("Primes = [ ");
  for (int i=0; i<size; i++)
    printf("%d ", array_of_primes[i]);
  printf("]");
}
