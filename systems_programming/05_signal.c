#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  pid_t pid1;
  pid1 = fork();
  if (pid1 == 0) {
    while (1) {
      printf("Child 1 is active\n");
      sleep(1);
    }
  }

  pid_t pid2;
  pid2 = fork();
  if (pid2 == 0) {
    while (1) {
      printf("Child 2 is active\n");
      sleep(1);
    }
  }

  sleep(2);
  kill(pid1, SIGSTOP);
  printf("Suspended Child 1\n");
  sleep(2);
  kill(pid1, SIGCONT);
  printf("Resumed Child 1\n");
  sleep(2);

  kill(pid1, SIGINT);
  printf("Killed Child 1\n");
  sleep(2);
  kill(pid2, SIGINT);
  printf("Killed Child 2\n");
}
