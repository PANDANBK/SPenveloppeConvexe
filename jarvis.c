#include "jarvis.h"

size_t aleat(size_t min, size_t max)
{
  return (rand() % (max - min + 1)) + min;
}

int compa_most_left(const struct vec *p1, const struct vec *p2, const void *ctx)
{
  assert(p1 != NULL);
  assert(p2 != NULL);

  return (p1->x - p2->x);
}

struct vec *vecset_random(const struct vecset *self)
{
  assert(self != NULL);
  return &self->data[aleat(0, self->size - 1)];
}

void jarvis_march(const struct vecset *in, struct vecset *out)
{
  assert(in != NULL);

  vecset_create(out);

  // Si taille < 3, pas besoin de calculs
  if(in->size <= 3)
  {
    for(size_t i = 0; i < in->size; i++)
    {
      vecset_add(out, in->data[i]);
    }
    return;
  }

  srand(time(NULL));

  const struct vec *f = vecset_min(in, compa_most_left, NULL);
  const struct vec *c = f;

  do
  {
    vecset_add(out, *c);
    struct vec *n;

    do
    {
      n = vecset_random(in);
    } while(n->x == c->x && n->y == c->y);

    for(size_t i = 0; i < in->size; i++)
    {
      if(!is_left_turn(c, n, &in->data[i]))
      {
        n = &in->data[i];
      }
    }
    c = n;

  } while(f->x != c->x && f->y != c->y);

  // Rien à retourner, out est déjà modifié
}
