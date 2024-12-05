#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  printf("Hello (pid:%d)\n", getpid());
  int rc = fork();

  if (rc < 0) {
    exit(1);
  } else if (rc == 0) {
    printf("Child process, pid: %d\n", getpid());
    exit(1);
  } else {
    int rc_wait = wait(NULL);
    printf("pid:%d , child:%d , rc_wait: %d\n", getpid(), rc, rc_wait);
    return 0;
  }
}
