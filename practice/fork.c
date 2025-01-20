#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // linux specific API

int main(void) {
  int id = fork();
  /*printf("Hello World from id: %d\n", id);*/
  if (id == 0) {
    printf("Hello from child process\n");
  } else {
    printf("Hello from parent process\n");
  }
  return 0;
}
