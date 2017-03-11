#include "hull.h"

int main()
{
  printf("Hello World!\n");
  return 0;
}

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

void vector_set_sort(struct vecset *self, comp_func_t func, const void *ctx)
{

}

void vecset_push(struct vecset *self, struct vec p)
{

}

void vecset_pop(struct vecset *self)
{

}

const struct vec *vecset_top(const struct vecset *self)
{
  return NULL;
}

const struct vec *vecset_second(const struct vecset *self)
{
  return NULL;
}
