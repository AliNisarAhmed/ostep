#include <stdlib.h>
int main(void) {
  int *array = (int *)malloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    array[i] = i + 1;
  }
}
