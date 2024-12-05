#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
  if (argc > 3) {
    printf("Please provide only 2 arguments\n");
  }

  int number_of_bytes = 0;
  int run_time = 0;

  if (sscanf(argv[1], "%i", &number_of_bytes) != 1) {
    printf("2nd argument Not an integer\n");
    exit(1);
  }

  if (sscanf(argv[2], "%i", &run_time) != 1) {
    printf("3rd argument Not an integer\n");
    exit(1);
  }

  char *array = (char *)malloc(sizeof(char) * number_of_bytes);

  struct timeval cur_time;
  time_t cur, end;
  gettimeofday(&cur_time, NULL);
  cur = cur_time.tv_sec;
  end = cur + run_time;

  int i;
  while (cur < end) {
    for (i = 0; i < number_of_bytes; i++) {
      array[i] = 1;
    }
    gettimeofday(&cur_time, NULL);
    cur = cur_time.tv_sec;
    printf("still running...\n");
  }

  free(array);
  exit(0);
}
