#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

void collatz_conjecture(unsigned);

int main(int argc, char **argv) {
  unsigned num;
  pid_t pid;

  if (argc < 2 || (num = atoi(argv[1])) <= 0) {
    printf("Usage: ./a.out <positive number>\n");
    return 1;
  }

  pid = fork();
  
  if (pid < 0) {
    printf("Some errors occurred while forking the program...\n");
    return 1;
  } else if (pid > 0)
    wait(NULL);
  else
    collatz_conjecture(num);
 
  return 0;
}

void collatz_conjecture(unsigned num) {
  while(num != 1) { //The sequence will always end with a 1
    printf("%d, ", num);
    num = (num%2) ? (3*num + 1) : (num / 2);
  }
  
  printf("1\n");
}
