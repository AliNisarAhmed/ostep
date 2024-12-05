#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int x = 100;
  int rc = fork();

  if (rc < 0) {
    exit(1);
  } else if (rc == 0) {
    x = x + 10;
    printf("Child process: %d, x: %d\n", getpid(), x);
  } else {
    // int rc_wait = wait(NULL);
    x = x + 55;
    printf("Parent process: %d, x: %d\n", getpid(), x);
  }

  return 0;
}
