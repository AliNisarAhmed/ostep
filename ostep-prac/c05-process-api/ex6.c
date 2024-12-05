#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();

  if (rc == 0) {
    int stat_loc = -100;
    pid_t wait_result = waitpid(0, &stat_loc, 0);
    printf("Child: %d, wait_result: %d\n", getpid(), (int)wait_result);
  } else {
    int stat_loc = -200;
    // -1 means wait for any child processes
    pid_t wait_result = waitpid(-1, &stat_loc, 0);
    printf("Parent:%d, wait_result: %d\n", getpid(), (int)wait_result);
  }

  return 0;
}
