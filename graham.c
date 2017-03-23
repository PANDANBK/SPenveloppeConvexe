#include "graham.h"

int compa_lowest(const struct vec *p1, const struct vec *p2, const void *ctx)
{
  assert(p1 != NULL);
  assert(p2 != NULL);

  return p1->y == p2->y ? p1->x - p2->x : p1->y - p2->y;
}

int compa_angle(const struct vec *p1, const struct vec *p2, const void *ctx)
{
  assert(p1 != NULL);
  assert(p2 != NULL);
  assert(ctx != NULL);

  const struct vec *p3 = ctx;

  // Possibilité d'utiliser atan2
  double a1;
  if(p1->y != p3->y)
  {
    a1 = atan( (p1->y - p3->y)/(p1->x - p3->x) );
    if(a1 < 0)
      a1 += PI;
  }
  else
  {
    a1 = 0;
  }

  double a2;
  if(p2->y != p3->y)
  {
    a2 = atan( (p2->y - p3->y)/(p2->x - p3->x) );
    if(a2 < 0)
      a2 += PI;
  }
  else
  {
    a2 = 0;
  }

  if(a1 == a2)
  {
    if(p1->x - p2->x < 0)
      return -1;
    else if(p1->x - p2->x > 0)
      return 1;
    else
      return 0;
  }

  if(a1 - a2 < 0)
    return -1;
  else if(a1 - a2 > 0)
    return 1;
  else
    return 0;
}

void graham_scan(const struct vecset *in, struct vecset *out)
{
  assert(in != NULL);

  vecset_create(out);
  // Solution triviale
  if(in->size <= 2)
  {
    for(size_t i = 0; i < in->size; i++)
    {
      vecset_add(out, in->data[i]);
    }
    return;
  }

  const struct vec *b = vecset_min(in, compa_lowest, NULL);

  // Tri de in -> Création d'un nouvel ensemble qu'on va pouvoir trier
  struct vecset s;
  vecset_create(&s);
  for(size_t i = 0; i < in->size; i++)
  {
    vecset_add(&s, in->data[i]);
  }
  vecset_sort(&s, compa_angle, b);

  const struct vec *f = &s.data[1];

  vecset_push(out, *b);

  vecset_push(out, *f);

  for(size_t i = 0; i < s.size; i++)
  {
    if( (s.data[i].x == b->x && s.data[i].y == b->y) || (s.data[i].x == f->x && s.data[i].y == f->y) )
    {
      continue;
    }

    // second et top dans la condition afin d'être mis à jour à chaque boucle
    while(out->size >= 2 && is_right_turn(vecset_second(out), vecset_top(out), &s.data[i]))
    {
      vecset_pop(out);
    }
    vecset_push(out, s.data[i]);
  }
  // Libération de la mémoire
  vecset_destroy(&s);
}
