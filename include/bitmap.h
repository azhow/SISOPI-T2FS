#pragma once
#include <stdint.h>
#include <stdbool.h>

// #define WORD_BIT (char)(sizeof(char)*8)

typedef struct bitmap {
  char *map;
  int size;
  bool (*get)(struct bitmap *, int);
  void (*set)(struct bitmap *, int);
  void (*reset)(struct bitmap *, int);
} bitmap;

bitmap *bitmap_init (int size);
void bitmap_free (bitmap *bitmap);