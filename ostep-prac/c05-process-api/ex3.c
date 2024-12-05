#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();

  if (rc < 0) {

  } else if (rc == 0) {
    printf("hello\n");  
  } else {
    sleep(2);
    printf("goodbye\n");
  }

  return 0;
}
