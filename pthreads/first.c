#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "generazione del nuovo processo fallita");
    return 1;
  } else if (pid == 0) {
    execlp("/bin/ls", "ls", NULL);
    printf("LINE J");
  } else {
    wait(NULL);
    printf("il processo figlio ha terminato");
  }

  return 0;
}
