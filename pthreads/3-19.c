#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid;

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Errore durante la creazione del figlio");
    return 1;
  } else if (pid == 0) {
    printf("Creazione figlio");
    execlp("/bin/sleep 100s", "sleep", NULL);
  } else if (pid > 0)
    printf("Il padre non attende");

  return 0;
}
