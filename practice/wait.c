#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> // linux specific API

int main(void) {
  int id = fork();

  int n;
  if (id == 0) {
    n = 1;
  } else {
    n = 6;
  }

  if (id != 0) {
    int wstatus;
    wait(&wstatus); // only in parent process - parent waits for child
    printf("wait status: %d\n", wstatus);
  }

  for (int i = n; i < n + 5; i++) {
    printf("%d ", i);
    fflush(stdout);
  }
  printf("\n");

  return 0;
}

/* NOTES
 * the child should terminate first before the parent process terminates
 */
