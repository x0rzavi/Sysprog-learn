#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
int in = 0;    // Index for producer to insert
int out = 0;   // Index for consumer to remove

// Function for the producer
void producer() {
  if (count < BUFFER_SIZE) { // Check if buffer is not full
    int item = rand() % 100; // Produce an item
    buffer[in] = item;       // Insert item in the buffer
    in = (in + 1) % BUFFER_SIZE;
    count++;
    printf("Producer produced: %d\n", item);
  } else {
    printf("Buffer is full! Producer is waiting...\n");
  }
}

// Function for the consumer
void consumer() {
  if (count > 0) {          // Check if buffer is not empty
    int item = buffer[out]; // Remove item from buffer
    out = (out + 1) % BUFFER_SIZE;
    count--;
    printf("Consumer consumed: %d\n", item);
  } else {
    printf("Buffer is empty! Consumer is waiting...\n");
  }
}

// Main function
int main() {
  int choice;

  while (1) {
    printf("\n1. Produce\n2. Consume\n3. Exit\nChoose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      producer();
      break;
    case 2:
      consumer();
      break;
    case 3:
      exit(0);
    default:
      printf("Invalid choice!\n");
    }

    // Simulate time delay
    sleep(1);
  }

  return 0;
}
