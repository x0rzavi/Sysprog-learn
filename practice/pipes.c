#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int fd[2];
  if (pipe(fd) == -1) { // save file descriptors in fd[2]
    return 1;
  }

  pid_t fork_pid;
  fork_pid = fork(); // child inherits the file descriptors - each process can
                     // now independently open or close the file descriptors
                     // manage each one ourselves
                     // child and parent each has 2 fds
  if (fork_pid == 0) {
    close(fd[0]); // we don't need to read inside child

    int x;
    printf("Input: ");
    scanf("%d", &x);

    write(fd[1], &x, sizeof(int)); // write to write end of pipe from child
    close(fd[1]); // tells anybody listening on fd that it has been closed
  } else {
    close(fd[1]); // we don't need to write inside child

    int y;
    read(fd[0], &y, sizeof(int)); // read from read end of pipe from parent
    printf("Got from child process: %d\n", y);

    close(fd[0]); // reading done
  }

  return 0;
}

/* NOTES
 * in memory file - which has a buffer
 * file descriptors - key to access the ends
 * pipe has 2 ends
 * fd[0] - read end
 * fd[1] - write end
 * */
