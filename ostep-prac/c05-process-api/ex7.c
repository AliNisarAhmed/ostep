#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();

  if (rc < 0) {
    
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("Child trying to print\n"); // with the above line this will not print
  } else {
    wait(NULL);
    printf("Parent\n");
  }

  return 0;

}
