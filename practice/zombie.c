#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t fork_pid;
  fork_pid = fork();

  if (fork_pid == 0) {
    printf("I am child process id: %d\n", getpid());
    printf("My parent process id: %d\n", getppid());
    system("ps -f");
  } else {
    /*
    wait(NULL); // makes parent wait for child to change state - avoid becoming
                // zombie
    */
    sleep(2); // since parent is sleeping - child finishes execution
    printf("I am parent process id: %d\n", getpid());
    printf("My child process id: %d\n", fork_pid);
    system("ps -f");
  }

  return 0;
}

/* NOTES
 * if child finishes, then parent is responsible for clearing all entries
 * related to the child process in the system
 * child process finishes without indicating the parent
 * parent never knows that child finished
 * parent assumes that child exists in the system
 * child becomes zombie/defunct process
 * */
