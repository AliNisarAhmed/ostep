#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  int file = open("./ex2_file.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
  int rc = fork();

  if (rc < 0) {

  } else if (rc == 0) {
    char *child_buff = "I am a child\n";
    write(file, child_buff, strlen(child_buff));
  } else {
    char *parent_buff = "I am a parent\n";
    write(file, parent_buff, strlen(parent_buff));
  }
  return 0;
}
