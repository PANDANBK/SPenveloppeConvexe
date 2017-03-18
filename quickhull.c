#include "quickhull.h"

void quickhull(const struct vecset *in, struct vecset *out)
{
  assert(in != NULL);

  // Création de l'ensemble de sortie
  vecset_create(out);

  // Si il n'y a que deux points, la solution est triviale
  if(in->size <= 2)
  {
    // Ajout des points de in dans out
    for(size_t i = 0; i < in->size; i++)
    {
      vecset_add(out, in->data[i]);
    }
    // Fin de la fonction
    return;
  }

  // Point le plus à gauche de l'ensemble
  const struct vec *a = vecset_min(in, compa_abscisses, NULL);
  // Point le plus à droite de l'ensemble
  const struct vec *b = vecset_max(in, compa_abscisses, NULL);

  // Premier sous-ensemble
  struct vecset s1;
  vecset_create(&s1);
  // Second sous-ensemble
  struct vecset s2;
  vecset_create(&s2);

  // Parcours de l'ensemble de départ
  for(size_t i = 0; i < in->size; i++)
  {
    // Si le point actuel est a (plus à gauche), on passe le tour
    if(in->data[i].x == a->x && in->data[i].y == a->y)
      continue;
    // Si le point actuel est b (plus à droite), on passe le tour
    if(in->data[i].x == b->x && in->data[i].y == b->y)
      continue;

    // Si le point I est à gauche de (ab)
    if(is_left_turn(a, b, &in->data[i]))
    {
      vecset_add(&s1, in->data[i]);
    }
    else // Autres points
    {
      vecset_add(&s2, in->data[i]);
    }
  }

  // Sortie de la récursion sur S1 (gauche)
  struct vecset r1;
  findhull(&s1, &r1, a, b);
  // Libération de s1 (plus utilisé)
  vecset_destroy(&s1);

  // Sortie de la récursion sur S2 (droite)
  struct vecset r2;
  findhull(&s2, &r2, b, a);
  // Libération de s2 (plus utilisé)
  vecset_destroy(&s2);

  // Mise à jour de la sortie

  vecset_add(out, *a);
  // Ajout de R1 complet
  for(size_t i = 0; i < r1.size; i++)
  {
    vecset_add(out, r1.data[i]);
  }
  vecset_add(out, *b);
  // Ajout de R2 complet
  for(size_t i = 0; i < r2.size; i++)
  {
    vecset_add(out, r2.data[i]);
  }

  // Libérations de R1 et R2
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

  // Création de la sortie
  vecset_create(out);

  // Rien n'est fait si l'ensemble d'entrée est vide
  if(s->size == 0)
  {
    return;
  }

  // Calcul du point le plus loin de la droite (xy)
  struct vec m = s->data[0];
  double maxDistance = distanceMin(x, y, &m);
  for(size_t i = 1; i < s->size; i++)
  {
    double newDistance = distanceMin(x, y, &s->data[i]);
    // Si une distance dépasse la plus grande distance, elle la remplace
    if(newDistance > maxDistance)
    {
      maxDistance = newDistance;
      m = s->data[i];
    }
  }
  // m contient donc le point le plus éloigné de la droite (xy)

  // Création du premier sous-ensemble
  struct vecset s1;
  vecset_create(&s1);
  // Second sous-ensemble
  struct vecset s2;
  vecset_create(&s2);

  // Parcours de l'entrée
  for(size_t i = 0; i < s->size; i++)
  {
    // Si m est le point actuel, on passe ce tour
    if(s->data[i].x == m.x && s->data[i].y == m.y)
      continue;

    // Si le point I est à gauche de la droite (xm) - strictement
    if( !is_left_turn(&m, x, &s->data[i]) )
    {
      vecset_add(&s1, s->data[i]);
    }
    // Sinon si le point I est à gauche de la droite (my) - strictement
    else if( !is_left_turn(y, &m, &s->data[i]) )
    {
      vecset_add(&s2, s->data[i]);
    }
  }

  // Ensemble de sortie de la récursion sur S1
  struct vecset r1;
  findhull(&s1, &r1, x, &m);
  // Libération de S1
  vecset_destroy(&s1);

  // Ensemble de sortie de la récursion sur S2
  struct vecset r2;
  findhull(&s2, &r2, &m, y);
  // Libération de S2
  vecset_destroy(&s2);

  // Mise à jour de la sortie
  for(size_t i = 0; i < r1.size; i++)
  {
    vecset_add(out, r1.data[i]);
  }

  vecset_add(out, m);

  for(size_t i = 0; i < r2.size; i++)
  {
    vecset_add(out, r2.data[i]);
  }

  // Libération de R1 et R2
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
