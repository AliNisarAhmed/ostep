#include <stdlib.h>

int main(void) {
  int *data = (int *)malloc(sizeof(int) * 100);
  data[100] = 0;
}
