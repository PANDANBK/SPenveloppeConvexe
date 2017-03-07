#include "hull.h"

double dot(const struct vec *v1, const struct vec *v2)
{
  assert(v1 != NULL && v2 != NULL);

  return (v1->x * v2->x) + (v1->y * v2->y);
}

double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3)
{
  return 0;
}

bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3)
{
  return false;
}
