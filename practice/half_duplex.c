#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int fds0[2]; // parent => child
  int fds1[2]; // child => parent
  if (pipe(fds0) == -1)
    return 1;
  if (pipe(fds1) == -1)
    return 1;

  pid_t forkpid;
  forkpid = fork();

  if (forkpid == -1) {
    return 1;
  } else if (forkpid == 0) { // child process
    int num;
    read(fds0[0], &num, sizeof(int));
    printf("read from child %d\n", num);

    int result;
    result = num * 5;

    write(fds1[1], &result, sizeof(int));
    printf("write from child %d\n", result);
  } else { // parent process
    int num;
    printf("Enter number: ");
    scanf("%d", &num);

    write(fds0[1], &num, sizeof(int));
    printf("write from parent %d\n", num);

    int result;
    read(fds1[0], &result, sizeof(int));
    printf("read from parent %d\n", result);
  }

  return 0;
}
