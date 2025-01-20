#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t fork_pid;
  fork_pid = fork();

  if (fork_pid == -1) {
    return 1;
  }

  if (fork_pid == 0) {
    while (1) {
      printf("I am in child\n");
      usleep(50000);
    }
  } else {
    kill(fork_pid, SIGSTOP); // print nothing by default

    int sec;
    do {
      printf("Enter seconds to execute process for: ");
      scanf("%d", &sec);
      if (sec > 0) {
        kill(fork_pid, SIGCONT);
        sleep(sec);
        kill(fork_pid, SIGSTOP);
      }
    } while (sec > 0);

    kill(fork_pid, SIGKILL); // sends a signal to process - doesn't kill -
                             // process knows what to do with the signal
    wait(NULL);
  }

  return 0;
}

/* NOTES
 * send a notification (int) to a process
 * tell process what to do
 * SIGKILL - kill process
 * SIGSTOP - pauses execution
 * SIGCONT - continue execution
 * SIGINT - terminate process gracefully
 * Ctrl-Z to pause a process - SIGTSTP
 * */
