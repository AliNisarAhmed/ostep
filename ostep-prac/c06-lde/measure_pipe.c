#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(void) {
  int loops = 10000;
  struct timeval time_before, time_after;

  int p1[2];
  int p2[2];
  cpu_set_t cpu_set;
  // https://linux.die.net/man/3/cpu_zero
  CPU_ZERO(&cpu_set);
  CPU_SET(0, &cpu_set);

  if (pipe(p1) < 0) {
    printf("pipe 1 error\n");
    exit(1);
  }

  if (pipe(p2) < 0) {
    printf("pipe 2 error\n");
    exit(1);
  }

  int rc = fork();

  if (rc < 0) {
    printf("fork failed\n");
  } else if (rc == 0) {
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

    for (int i = 0; i < loops; i++) {
      write(p1[0], NULL, 0);
      read(p2[1], NULL, 0);
    }
  } else {
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);

    gettimeofday(&time_before, NULL);

    for (int i = 0; i < loops; i++) {
      write(p2[0], NULL, 0);
      read(p1[1], NULL, 0);
    }

    gettimeofday(&time_after, NULL);
    printf("Average context switch: %f microseconds\n",
           (1000000 * time_after.tv_sec + time_after.tv_usec -
            1000000 * time_before.tv_sec - time_before.tv_usec) /
               (float)loops);
  }
}
