#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define QUEUE_SIZE 20

void enqueue(int data);
int dequeue();

int queue[QUEUE_SIZE];
int items_buffer[QUEUE_SIZE];
int item_number = 0;
int rear = -1;
int front = -1;

void down_binary(int *semaphore);
void up_binary(int *semaphore);
void down_counting(int *semaphore);
void up_counting(int *semaphore);
void produce_item(int *binary_semaphore, int *counting_semaphore_full,
                  int *counting_semaphore_empty);
void consume_item(int *binary_semaphore, int *counting_semaphore_full,
                  int *counting_semaphore_empty);

int main(void) {
  int binary_semaphore = 1;
  int counting_semaphore_full = 0;
  int counting_semaphore_empty = QUEUE_SIZE;

  pid_t forkpid;
  forkpid = fork();

  if (forkpid == -1) {
    return 1;
  } else if (forkpid == 0) { // child process
    for (int i = 0; i < 10; i++) {
      consume_item(&binary_semaphore, &counting_semaphore_full,
                   &counting_semaphore_empty);
    }
  } else { // parent process
    for (int i = 0; i < 10; i++) {
      produce_item(&binary_semaphore, &counting_semaphore_full,
                   &counting_semaphore_empty);
    }
    wait(NULL);
  }
  return 0;
}

void enqueue(int data) {
  if (rear == QUEUE_SIZE - 1) {
    return;
  }

  if (front == -1) {
    front = 0;
  }
  queue[rear++] = data;
}

int dequeue() {
  if (front == -1 || front > rear) {
    return -1;
  }
  return queue[front++];
}

void down_binary(int *semaphore) {
  while (*semaphore == 0)
    ;
  *semaphore = 0;
}

void up_binary(int *semaphore) { *semaphore = 1; }

void down_counting(int *semaphore) {
  *semaphore -= 1;
  if (*semaphore < 0) {
    enqueue(*semaphore);
    while (*semaphore < 0)
      ;
  }
}

void up_counting(int *semaphore) {
  *semaphore += 1;
  if (*semaphore <= 0) {
    dequeue();
  }
}

void produce_item(int *binary_semaphore, int *counting_semaphore_full,
                  int *counting_semaphore_empty) {
  down_counting(counting_semaphore_empty);
  down_binary(binary_semaphore);
  items_buffer[item_number] = item_number;
  printf("Produced item %d\n", item_number);
  ++item_number;
  item_number = item_number % QUEUE_SIZE;
  up_binary(binary_semaphore);
  up_counting(counting_semaphore_full);
}

void consume_item(int *binary_semaphore, int *counting_semaphore_full,
                  int *counting_semaphore_empty) {
  down_counting(counting_semaphore_full);
  down_binary(binary_semaphore);
  item_number = items_buffer[item_number];
  printf("Consumed item %d\n", item_number);
  --item_number;
  item_number = item_number % QUEUE_SIZE;
  up_binary(binary_semaphore);
  up_counting(counting_semaphore_empty);
}
