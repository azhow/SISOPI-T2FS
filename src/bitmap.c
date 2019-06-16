#include "bitmap.h"

#include <stdlib.h>
#include <stdio.h>

/* bitmap functions */
bool bitmap_get (bitmap *, int);
void bitmap_set (bitmap *, int);
void bitmap_reset (bitmap *, int);

bitmap *bitmap_init (int size)
/* Creates an empty bitmap with @size chars */
{
  int i;
  bitmap *temp = (bitmap *) calloc (1, sizeof(bitmap));
  temp->map = (char *) calloc (size, sizeof(char));
  temp->size = size;
  temp->get = &bitmap_get;
  temp->set = &bitmap_set;
  temp->reset = &bitmap_reset;

  for (i=0; i < size; i++){
    temp->map[i] = '1';
  }
  return temp;
}

void bitmap_free (bitmap *bitmap)
/* Destroys the @bitmap */
{
  free (bitmap->map);
  free (bitmap);
}

bool bitmap_get (bitmap *self, int n)
/* Returns the value of the @n'th bit of the bitmap */
{
  return self->map[n];
}

void bitmap_set (bitmap *self, int n)
/* Sets the @n'th bit of the bitmap to true */
{
  self->map[n] = '0';
}

void bitmap_reset (bitmap *self, int n)
/* Sets the @n'th bit of the bitmap to false */
{
  self->map[n] = '1';
}


// int bitmapSearch(bitmap *bitmap) {
// /* Finds the first n value in bitmap after start */
// /* size is the Bitmap size in bytes */
//     int i;
//     /* size is now the Bitmap size in bits */
//     for(i = 0, bitmap->size *= WORD_BIT; i < bitmap->size; i++)
//         if(bitmapGet(bitmap,i) == n)
//             return i;
//     return -1;
// }