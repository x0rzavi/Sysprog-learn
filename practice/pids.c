#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> // linux specific API

int main(void) {
  int id = fork();
  if (id == 0) {
    sleep(2); // let parent terminate while the child wait
  }

  printf("current ID: %d, parent ID: %d\n", getpid(), getppid());

  /* uncomment to not let parent terminate before child
  int waitStatus = wait(NULL);
  if (waitStatus == -1) {
    printf("No children to wait for\n");
  } else {
    printf("%d finished execution", waitStatus);
  }
  */

  return 0;
}

/* NOTES
 * parent died before child - orphan child
 * child got assigned a new parent than the original parent
 * leads to a memory leak
 * need to wait for the child to finish
 */
