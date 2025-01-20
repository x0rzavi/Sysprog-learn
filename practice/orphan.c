#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t fork_pid;
  fork_pid = fork();

  if (fork_pid == 0) {
    sleep(
        2); // child sleeps and transfers control to parent which finishes early
    printf("I am child process id: %d\n", getpid());
    printf("My parent process id: %d\n", getppid());
    system("ps -f");
  } else {
    printf("I am parent process id: %d\n", getpid());
    printf("My child process id: %d\n", fork_pid);
    system("ps -f");
  }

  return 0;
}

/* NOTES
 * parent terminates before child
 * child cannot print its correct parent
 * */
