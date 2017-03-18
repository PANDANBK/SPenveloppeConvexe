#include "quickhull.h"

void quickhull(const struct vecset *in, struct vecset *out)
{
  assert(in != NULL);
  // vecset_destroy(out);
  vecset_create(out);

  const struct vec *a = vecset_min(in, compa_abscisses, NULL);
  const struct vec *b = vecset_max(in, compa_abscisses, NULL);

  //printf("MIN : %f %f\n", a->x, a->y);
  //printf("MAX : %f %f\n", b->x, b->y);

  struct vecset s1;
  vecset_create(&s1);
  struct vecset s2;
  vecset_create(&s2);

  for(size_t i = 0; i < in->size; i++)
  {
    if(in->data[i].x == a->x && in->data[i].y == a->y)
      continue;
    if(in->data[i].x == b->x && in->data[i].y == b->y)
      continue;

    if(is_left_turn(a, b, &in->data[i]))
    {
      vecset_add(&s1, in->data[i]);
    }
    else
    {
      vecset_add(&s2, in->data[i]);
    }
  }

  struct vecset r1;
  findhull(&s1, &r1, a, b);
  vecset_destroy(&s1);

  struct vecset r2;
  findhull(&s2, &r2, b, a);
  vecset_destroy(&s2);

  vecset_add(out, *a);
  for(size_t i = 0; i < r1.size; i++)
  {
    vecset_add(out, r1.data[i]);
  }
  vecset_add(out, *b);
  for(size_t i = 0; i < r2.size; i++)
  {
    vecset_add(out, r2.data[i]);
  }
  vecset_destroy(&r1);
  vecset_destroy(&r2);
}

int compa_abscisses(const struct vec *p1, const struct vec *p2, const void *ctx)
{
  assert(p1 != NULL);
  assert(p2 != NULL);

  return p1->x - p2->x;
}

void findhull(const struct vecset *s, struct vecset *out, const struct vec *x, const struct vec *y)
{
  assert(s != NULL);

  vecset_create(out);

  if(s->size == 0)
  {
    return;
  }

  /*printf("--- S AVANT DIST ---\n");
  for(size_t k = 0; k < s->size; k++)
  {
    printf("s %zu : %f %f\n", k, s->data[k].x, s->data[k].y);
  }*/
  struct vec m = s->data[0];
  double maxDistance = distanceMin(x, y, &m);
  //printf("Distance init 0 : %f %f - d : %f\n", s->data[0].x, s->data[0].y, distanceMin(x, y, &m));
  for(size_t i = 1; i < s->size; i++)
  {
    double newDistance = distanceMin(x, y, &s->data[i]);
    //printf("Distance moindre %zu : %f %f - d : %f\n", i, s->data[i].x, s->data[i].y, distanceMin(x, y, &s->data[i]));
    if(newDistance > maxDistance)
    {
      maxDistance = newDistance;
      m = s->data[i];
      //printf("Distance max %zu : %f %f - d : %f\n", i, s->data[i].x, s->data[i].y, distanceMin(x, y, &s->data[i]));
    }
  }

  struct vecset s1;
  vecset_create(&s1);
  struct vecset s2;
  vecset_create(&s2);

  for(size_t i = 0; i < s->size; i++)
  {
    if(s->data[i].x == m.x && s->data[i].y == m.y)
      continue;

    if( !is_left_turn(&m, x, &s->data[i]) )
    {
      vecset_add(&s1, s->data[i]);
    }

    else if( !is_left_turn(y, &m, &s->data[i]) )
    {
      vecset_add(&s2, s->data[i]);
    }
  }

  struct vecset r1;
  findhull(&s1, &r1, x, &m);
  vecset_destroy(&s1);

  struct vecset r2;
  findhull(&s2, &r2, &m, y);
  vecset_destroy(&s2);

  for(size_t i = 0; i < r1.size; i++)
  {
    vecset_add(out, r1.data[i]);
  }

  vecset_add(out, m);

  for(size_t i = 0; i < r2.size; i++)
  {
    vecset_add(out, r2.data[i]);
  }

  vecset_destroy(&r1);
  vecset_destroy(&r2);
}

double carre(double x)
{
  return x * x;
}

double distance(const struct vec *a, const struct vec *b)
{
  return carre(a->x - b->x) + carre(a->y - b->y);
}

double min(double x, double y)
{
  return x < y ? x : y;
}

double max(double x, double y)
{
  return x > y ? x : y;
}

double distanceMin(const struct vec *a, const struct vec *b, const struct vec *p)
{
  assert(a != NULL);
  assert(b != NULL);
  assert(p != NULL);

  double dist = distance(a, b);

  if(dist == 0)
    return distance(p, a);

  double tmp = ( (p->x - a->x) * (b->x - a->x) + (p->y - a->y) * (b->y - a->y) ) / dist;

  tmp = max(0, min(1, tmp));

  struct vec t;
  t.x = a->x + tmp * (b->x - a->x);
  t.y = a->y + tmp * (b->y - a->y);
  return sqrt(distance(p, &t));
}
