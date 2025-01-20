#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // linux specific API

int main(void) {
  int id = fork();
  if (id != 0) {
    fork();
  }
  printf("Hello World\n");
  return 0;
}
