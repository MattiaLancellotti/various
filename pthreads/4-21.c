#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define THREAD_NUM 3
#define MIN_ARGS 2

struct list_t {
  int *list;
  int size;
};

int *init_list(int * /*list_num*/, int /*size*/);
int to_numbers(char * /*argv*/ [], int /*argv_size*/, int * /*list_num*/);
void print_nums(struct list_t /*list*/);
void *pthread_calc_average(void * /*list*/);
void *pthread_calc_min(void * /*list*/);
void *pthread_calc_max(void * /*list*/);

int average = 0, min = 0, max = 0;

int main(int argc, char *argv[]) {
  /* list of numbers to work on */
  struct list_t list= { .list = NULL, .size = 0};
  void *(*pthread_functions[THREAD_NUM])(void *) = {
    pthread_calc_average, 
    pthread_calc_min, 
    pthread_calc_max
  };

  /* pthreads */
  pthread_attr_t attrs[THREAD_NUM];
  pthread_t tids[THREAD_NUM];

  /* checking parameters */
  if (argc < MIN_ARGS) {
    fprintf(stderr, "%s: usage %s <numbers>", argv[0], argv[0]);
    return 1;
  }
  
  list.list = init_list(list.list, argc-1);
  list.size = argc-1;

  to_numbers(argv, argc, list.list);

  for (int i=0; i<THREAD_NUM; i++) {
    pthread_attr_init(attrs+i);
    pthread_create(tids+i, attrs+i, pthread_functions[i], (void *)&list);
    pthread_join(tids[i], NULL);
  }

  printf("Average = %d\n", average);
  printf("Min     = %d\n", min);
  printf("Max     = %d\n", max);

  return 0;
}

int *init_list(int *list_num, int size) {
  list_num = malloc(sizeof(int) * size);

  return list_num;
}

int to_numbers(char *argv[], int argv_size, int *list_num) {
  int i;

  for (i=1; i<argv_size; i++)
    list_num[i-1] = atoi(argv[i]);

  return i;
}

void print_nums(struct list_t list) {
  printf("list_num = ");
  for (int i=0; i<list.size; i++)
    printf("%d ", list.list[i]);

  printf("\n");
}

void *pthread_calc_average(void *list) {
  struct list_t thread_list = *(struct list_t *)list;
  int sum = 0, i = 0;

  for ( ; i<thread_list.size; i++)
    sum += thread_list.list[i];

  average = sum/i;
  return NULL;
}

void *pthread_calc_min(void *list) {
  struct list_t thread_list = *(struct list_t *)list;
  int tmin = thread_list.list[0];

  for (int i=1; i<thread_list.size; i++)
    if (tmin > thread_list.list[i])
      tmin = thread_list.list[i];

  min = tmin;
  return NULL;
}

void *pthread_calc_max(void *list) {
  struct list_t thread_list = *(struct list_t *)list;
  int tmax = thread_list.list[0];

  for (int i=1; i<thread_list.size; i++)
    if (tmax < thread_list.list[i])
      tmax = thread_list.list[i];

  max = tmax;
  return NULL;
}
