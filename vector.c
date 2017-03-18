#include "hull.h"

double dot(const struct vec *v1, const struct vec *v2)
{
  assert(v1 != NULL && v2 != NULL);

  return (v1->x * v2->x) + (v1->y * v2->y);
}

double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3)
{
  assert(p1 != NULL && p2 != NULL && p3 != NULL);

  return (p2->x - p1->x)*(p3->y - p1->y)-(p2->y - p1->y)*(p3->x - p1->x);
}

bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3)
{
  assert(p1 != NULL && p2 != NULL && p3 != NULL);
  
  return cross(p1, p2, p3) <= 0 ? true : false;
}
