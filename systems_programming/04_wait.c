#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t fork_pid;
  fork_pid = fork();

  if (fork_pid == -1) {
    printf("ERROR!\n");
  } else if (fork_pid == 0) {
    printf("Child process PID: %d, PPID: %d\n", getpid(), getppid());
    sleep(2);
  } else {
    wait(NULL); // wait for child process to finish executing
    printf("Parent process PID: %d, PPID: %d\n", getpid(), getppid());
  }
}
