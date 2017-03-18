#include "hull.h"

void vecset_create(struct vecset *self)
{
    assert(self != NULL);

    self->data = calloc(sizeof(struct vec), 6);
    self->size = 0;
    self->capacity = 6;
}

void vecset_destroy(struct vecset *self)
{
    assert(self != NULL);
    free(self->data);
    self->data = NULL;
}

void vecset_add(struct vecset *self, struct vec p)
{
  assert(self != NULL);

  if(self->size == self->capacity)
  {
    size_t newCapacity = self->capacity * 2;
    struct vec *newArray = malloc(newCapacity * sizeof(struct vec));
    memcpy(newArray, self->data, self->size * sizeof(struct vec));
    free(self->data);
    self->data = newArray;
    self->capacity = newCapacity;
  }

  self->data[self->size] = p;
  self->size++;
}

const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx)
{
  assert(self != NULL);

  if(self->size == 0)
    return NULL;

  if(self->size == 1)
    return self->data;

  size_t max = 0;
  for(size_t i = 1; i < self->size; i++)
  {
    if( func(&self->data[max], &self->data[i], ctx) < 0 )
    {
      max = i;
    }
  }

  return &self->data[max];
}

const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx)
{
  assert(self != NULL);

  if(self->size == 0)
    return NULL;

  if(self->size == 1)
    return self->data;

  size_t min = 0;
  for(size_t i = 1; i < self->size; i++)
  {
    if( func(&self->data[min], &self->data[i], ctx) > 0 )
    {
      min = i;
    }
  }

  return &self->data[min];
}

static int pivotage(struct vecset *self, comp_func_t func, const void *ctx, size_t indi, size_t indf, size_t pivot){

      size_t i, j;
      struct vec aux;

      aux = self->data[pivot];
      self->data[pivot] = self->data[indf];
      self->data[indf] = aux;
      j = indi;

      for (i = indi; i < indf; i++)
      {
        if ( func(&self->data[i], &self->data[indf], ctx) < 0 )
        {
          aux = self->data[i];
          self->data[i] = self->data[j];
          self->data[j] = aux;
          j++;
        }
      }
      aux = self->data[indf];
      self->data[indf] = self->data[j];
      self->data[j] = aux;
      return j;
}



static void triRapide(struct vecset *self, comp_func_t func, const void *ctx, size_t indi, size_t indf) {

      size_t iMedian, pivot;
      struct vec aux;
      if (indf == indi +1)
      {
        if ( func(&self->data[indf], &self->data[indi], ctx) < 0 )
        {
          aux = self->data[indi];
          self->data[indi] = self->data[indf];
          self->data[indf] = aux;
        }
      }
      else
      {
        pivot = (indi+indf)>>1;
        iMedian = pivotage(self, func, ctx, indi, indf, pivot);
        if (iMedian > indi+1)
        {
          triRapide(self, func, ctx, indi, iMedian-1);
        }
        if (iMedian < indf - 1)
        {
          triRapide(self, func, ctx, iMedian+1, indf);
        }
      }
}


void vecset_sort(struct vecset *self, comp_func_t func, const void *ctx)
{
  triRapide(self, func, ctx, 0, self->size - 1);
  // vecset_sort_rec(self, func, ctx, 0, self->size - 1);
}

void vecset_push(struct vecset *self, struct vec p)
{
  vecset_add(self, p);
}

void vecset_pop(struct vecset *self)
{
  assert(self != NULL);
  if(self->size > 0)
  {
    self->size--;
  }
}

const struct vec *vecset_top(const struct vecset *self)
{
  assert(self != NULL);

  return &self->data[self->size - 1];

  return NULL;
}

const struct vec *vecset_second(const struct vecset *self)
{
  assert(self != NULL);

  return &self->data[self->size - 2];

  return NULL;
}
