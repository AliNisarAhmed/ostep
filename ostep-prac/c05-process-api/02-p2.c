#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();

  if (rc < 1) {
    exit(1);
  } else if (rc == 0) {
    // child process
    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("02-p2.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);
    printf("child process end\n");
  } else {
    int rc_wait = wait(NULL);
    printf("parent of rc:%d\n", rc);
    return 0;
  }
}
