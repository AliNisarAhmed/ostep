#ifndef _VECTOR_
#define _VECTOR_

#include <stdbool.h>

typedef struct Vector {
  int size;
  int capacity;
  int *data;
} Vector;

Vector *Vector_create(int capacity);
void Vector_add(Vector *vector, int element);
int Vector_remove(Vector *vector);
bool Vector_is_full(Vector *vector);
void Vector_resize(Vector *vector, int new_capacity);
void Vector_free(Vector *vector);

#endif
