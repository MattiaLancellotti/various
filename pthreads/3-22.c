#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

void collatz_conjecture(unsigned, void *);

int main(int argc, char **argv) {
  const char *name = "COLLATZ";
  const int SIZE = 4096;
  unsigned num;
  pid_t pid;
  int shm_fd; //file descriptor
  void *ptr_read, *ptr_write;

  if (argc < 2 || (num = atoi(argv[1])) <= 0) {
    printf("Usage: ./a.out <positive number>\n");
    return 1;
  }

  //Creazione oggetto di memoria condivisa
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  ptr_write = ptr_read = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  pid = fork();
  
  if (pid < 0) {
    printf("Some errors occurred while forking the program...\n");
    return 1;
  } else if (pid > 0) {
    wait(NULL);

    printf("%s", (char *)ptr_read);
    shm_unlink(name);
  } else {
    collatz_conjecture(num, ptr_write);
  }
 
  return 0;
}

#define BUF_SIZ 512
void collatz_conjecture(unsigned num, void *ptr) {
  char buf[BUF_SIZ];

  while(num != 1) { //The sequence will always end with a 1
    sprintf(buf, "%d, ", num);
    sprintf(ptr, buf);
    num = (num%2) ? (3*num + 1) : (num / 2);
    ptr += strlen(buf);
  }
  
  sprintf(ptr, "1\n");
  printf("The son has finished\n");
}
