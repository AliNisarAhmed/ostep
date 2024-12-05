#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  printf("Hello main pid:%d\n", (int)getpid());

  int rc = fork();

  if (rc < 0) {
    fprintf(stdout, "Fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("In child process, pid:%d\n", getpid());
  } else {
    printf("In main, pid:%d parent of %d\n", getpid(), rc);
  }
  return 0;
}
