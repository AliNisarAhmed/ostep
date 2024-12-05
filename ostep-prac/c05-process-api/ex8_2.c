#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(void) {
  int rc1 = fork();
  int rc2;

  int p[2];
  int nbytes_read;
  char inbuf[MAX_LINE];

  if (pipe(p) < 0) {
    exit(1);
  }

  if (rc1 < 0) {
    exit(1);
  } else if (rc1 == 0) {
    close(p[0]);
    write(p[1], "Msg from rc1\n", 13);
    exit(0);
  } else {
    rc2 = fork();
    if (rc2 < 0) {
      printf("Second fork failed\n");
      exit(1);
    } else if (rc2 == 0) {
      close(p[1]);
      printf("receive msg from another child (%d)\n", getpid());
      int n = read(p[0], inbuf, MAX_LINE);
      printf("finished reading: %d\n", n);
      write(STDOUT_FILENO, inbuf, n);
      exit(0);
    } else {
      printf("Main block\n");
      printf("p[0]:%d, p[1]:%d\n", p[0], p[1]);
      close(p[0]);
      close(p[1]);
      waitpid(rc1, NULL, 0);
      waitpid(rc2, NULL, 0);
    }
  }

  return 0;
}
