#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Vector *Vector_create(int capacity) {
  Vector *v = (Vector *)malloc(sizeof(Vector));
  v->data = (int *)malloc(sizeof(int) * capacity);
  v->size = 0;
  v->capacity = capacity;
  return v;
}

bool Vector_is_full(Vector *vector) { return vector->size == vector->capacity; }

void Vector_add(Vector *vector, int element) {
  if (Vector_is_full(vector)) {
    Vector_resize(vector, vector->capacity * 2);
  }
  vector->data[vector->size++] = element;
}

void Vector_resize(Vector *vector, int new_capacity) {
  vector->data = realloc(vector->data, sizeof(int) * new_capacity);
  vector->capacity = new_capacity;
}

void Vector_free(Vector *v) {
  if (v->data != NULL) {
    free(v->data);
  }
  if (v != NULL) {
    free(v);
  }
}

int main(void) {
  Vector *v = Vector_create(2);
  Vector_add(v, 1);
  Vector_add(v, 2);
  printf("vector cap: %d\n", v->capacity);
  printf("vector size: %d\n", v->size);
  Vector_add(v, 3);
  Vector_add(v, 4);
  printf("vector cap after: %d\n", v->capacity);
  Vector_add(v, 5);
  printf("vector cap end: %d\n", v->capacity);

  for (int i = 0; i < v->size; i++) {
    printf("v element at index %d = %d\n", i, v->data[i]);
  }
  Vector_free(v);
}
