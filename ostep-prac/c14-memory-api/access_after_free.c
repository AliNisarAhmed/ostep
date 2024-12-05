#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int *data = (int *)malloc(sizeof(int) * 10);
  data[1] = 1000;
  printf("before free: data[1]: %d\n", data[1]);
  free(data);
  printf("after free: data[1]: %d\n", data[1]);
}
