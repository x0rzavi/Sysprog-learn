#include <stdio.h>
#define BUFFER_SIZE 5;

int mutex = 1;
int full_slots = 0;
int empty_slots = BUFFER_SIZE;
int item_num = 0;

void producer() {
  --mutex;

  ++full_slots;
  --empty_slots;
  printf("Produced item: %d\n", ++item_num);

  ++mutex;
}

void consumer() {
  --mutex;

  --full_slots;
  ++empty_slots;
  printf("Consumed item: %d\n", item_num--);

  ++mutex;
}

int main(void) {
  printf("1. Produce\n2. Consume\n3. Exit\n");

#pragma omp critical
  while (1) {
    printf("Enter choice: ");
    fflush(stdout);
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      if ((mutex == 1) && (empty_slots != 0)) {
        producer();
      } else {
        printf("Buffer full!\n");
      }
      break;

    case 2:
      if ((mutex == 1) && (full_slots != 0)) {
        consumer();
      } else {
        printf("Buffer empty!\n");
      }
      break;

    case 3:
      return 0;
    }
  }
}
