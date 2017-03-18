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

  //printf("Angle entre : (%f, %f) ; (%f, %f) ; (%f, %f)\n", p1->x, p1->y, p2->x, p2->y, p3->x, p3->y);


  /*double a1 = fabs(atan2(p1->x - p3->x, p1->y - p3->y));
  double a2 = fabs(atan2(p2->x - p3->x, p2->y - p3->y));*/

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
    //printf("= : %d\n", (int)((p1->x - p2->x)*1000));
    return (int)((p1->x - p2->x)*1000);
  }

  //printf("Res : %d\n", (int)((a1 - a2)*1000));
  return (int)((a1 - a2)*1000);

  //printf("1 : %f ; 2 : %f\n", a1, a2);

  // return a1 == a2 ? p1->x - p2->x : a1 - a2;
}

void graham_scan(const struct vecset *in, struct vecset *out)
{
  const struct vec *b = vecset_min(in, compa_lowest, NULL);

  // Tri de in -> Création d'un nouvel ensemble qu'on va pouvoir trier
  struct vecset s;
  vecset_create(&s);
  for(size_t i = 0; i < in->size; i++)
  {
    vecset_add(&s, in->data[i]);
  }
  vecset_sort(&s, compa_angle, b);

  /*printf("--- S TRIÉ ---\n");
  for(size_t k = 0; k < s.size; k++)
  {
    printf("out %zu : %f %f\n", k, s.data[k].x, s.data[k].y);
  }*/

  const struct vec *f = &s.data[1];

  vecset_create(out);
  /*printf("--- START ---\n");
  for(size_t k = 0; k < out->size; k++)
  {
    printf("out %zu : %f %f\n", k, out->data[k].x, out->data[k].y);
  }*/
  vecset_push(out, *b);
  /*printf("--- PUSH ---\n");
  for(size_t k = 0; k < out->size; k++)
  {
    printf("out %zu : %f %f\n", k, out->data[k].x, out->data[k].y);
  }*/
  vecset_push(out, *f);
  /*printf("--- PUSH ---\n");
  for(size_t k = 0; k < out->size; k++)
  {
    printf("out %zu : %f %f\n", k, out->data[k].x, out->data[k].y);
  }*/

  for(size_t i = 0; i < s.size; i++)
  {
    if( (s.data[i].x == b->x && s.data[i].y == b->y) || (s.data[i].x == f->x && s.data[i].y == f->y) )
    {
      continue;
    }
    //const struct vec *top = vecset_top(out);
    //const struct vec *second = vecset_second(out);
    while(out->size >= 2 && is_left_turn(vecset_second(out), vecset_top(out), &s.data[i]))
    {
      //printf("Pt (%f, %f)\n", s.data[i].x, s.data[i].y);
      vecset_pop(out);
      /*printf("--- POP ---\n");
      for(size_t k = 0; k < out->size; k++)
      {
        printf("out %zu : %f %f\n", k, out->data[k].x, out->data[k].y);
      }*/
    }
    vecset_push(out, s.data[i]);
    /*printf("--- PUSH ---\n");
    for(size_t k = 0; k < out->size; k++)
    {
      printf("out %zu : %f %f\n", k, out->data[k].x, out->data[k].y);
    }*/
  }
  vecset_destroy(&s);
}
