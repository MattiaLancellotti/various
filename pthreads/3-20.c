#include <stdio.h>
#include <stdlib.h>

#define MAX_PID 5000
#define MIN_PID 300

#define EXIT(x, y) if (!x) return y;

static char *pid_list = NULL;

int main(void) {
  return 0;
}

int allocate_map(void) {
  pid_list = malloc(sizeof(char)*(MAX_PID-MIN_PID));

  return pid_list ? 1 : -1;
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
