#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int rc = fork();

  if (rc < 0) {

  } else if (rc == 0) {
    char *myargs[2];
    close(STDOUT_FILENO);
    open("./ex4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    // myargs[0] = strdup("/bin/ls");
    // myargs[1] = NULL;
    // execl(myargs[0], myargs[1]);

    // myargs[0] = "ls";
    // myargs[1] = NULL;
    // execlp(myargs[0], NULL);
    
    // myargs[0] = "/bin/echo";
    // char *env_list = { "MYNAME=ali", NULL};
    // execle(myargs[0], "$MYNAME" , NULL, env_list);

    // execv("ls", NULL) // -> won't work
    // execv("/bin/ls", NULL);

    execvp("ls", NULL); // works 

  } else {
    wait(NULL);
    printf("I am parent\n");
  }

  return 0;
}
