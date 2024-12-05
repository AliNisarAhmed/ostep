#include <stdlib.h>

int main(void) {
  int *data = (int *)malloc(sizeof(int) * 10);
  data[5] = 1000;
  int *x = &data[5];
  free(x);
}
