#include "hull.h"

int main()
{
  printf("Hello World!\n");
  return 0;
}

void vecset_create(struct vecset *self)
{
    self->data = calloc(sizeof(struct vec), 6);
    self->size = 0;
    self->capacity = 6;
}

void vecset_destroy(struct vecset *self)
{
    free(self->data);
    self->data = NULL;
}

void vecset_add(struct vecset *self, struct vec p)
{

}

const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx)
{
  return NULL;
}

const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx)
{
  return NULL;
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
