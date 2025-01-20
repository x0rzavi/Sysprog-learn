#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFFER_SIZE 5

int mutex = 1;
int full_slots = 0;
int empty_slots = BUFFER_SIZE;
int item_num = 0;

void down();
void up();
void producer();
void consumer();

int main(void) {
  pid_t fork_pid;
  fork_pid = fork();

  if (fork_pid == -1) {
    return 1;
  } else if (fork_pid == 0) { // child
    for (int i = 0; i < BUFFER_SIZE; i++) {
      consumer();
    }
  } else { // parent
    for (int i = 0; i < BUFFER_SIZE; i++) {
      producer();
      sleep(1);
    }
    wait(NULL);
  }

  return 0;
}

void down() {
  while (mutex != 0) // busy waiting
    ;
  mutex = 0;
}

void up() { mutex = 1; }

void producer() {
  down();

  ++full_slots;
  --empty_slots;
  printf("Produced item: %d\n", ++item_num);

  up();
}

void consumer() {
  down();

  --full_slots;
  ++empty_slots;
  printf("Consumed item: %d\n", item_num--);

  up();
}
