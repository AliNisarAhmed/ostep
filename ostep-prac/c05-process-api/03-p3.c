#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();
  if (rc < 0) {
    exit(1);
  } else if (rc == 0) {
    // child process
    close(STDOUT_FILENO);
    open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("03-p3.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);
  } else {
    int rc_wait = wait(NULL);
  }
  return 0;
}
