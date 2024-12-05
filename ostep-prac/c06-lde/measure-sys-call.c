#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_OPERATIONS 1000000

int main(void) {
  int fd = open("1.txt", O_RDONLY, S_IRWXU);
  struct timeval start;
  struct timeval end;

  gettimeofday(&start, NULL);
  for (int i = 0; i < NUM_OPERATIONS; i++) {
    int b = read(fd, NULL, 0);
  }
  gettimeofday(&end, NULL);

  printf("System call: microseconds: %f\n\n",
         (float)(end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 +
                 start.tv_usec) /
             NUM_OPERATIONS);

  exit(0);
}
