#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_handler(int signal) { printf("Signal %d was caught\n", signal); }

int main(void) {
  signal(SIGINT, signal_handler);
  while (1)
    ;
}
