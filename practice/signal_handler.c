#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigtstp(int signal) { printf("Not allowed to stop\n"); }

int main(void) {
  signal(SIGTSTP, handle_sigtstp);

  int x;
  printf("Input number: ");
  scanf("%d", &x);
  printf("Result: %d\n", x * 5);

  return 0;
}
