#ifndef DEF_QUICKHULL
#define DEF_QUICKHULL

#include "hull.h"
#include <math.h>

/**
 * Implémente l'enveloppe rapide
 *
 * @param   const struct vecset     *in   Ensemble d'entrée
 * @param   const struct vecset     *in   Ensemble de sortie
 */
void quickhull(const struct vecset *in, struct vecset *out);

/**
 * Séparation de s en deux ensembles : gauche et droite de (xy)
 *
 * @param   const struct vecset     *s    Ensemble d'entrée
 * @param   struct vecset           *out  Ensemble de sortie
 * @param   const struct vec        *x    Premier point
 * @param   const struct vec        *y    Second point
 */
void findhull(const struct vecset *s, struct vecset *out, const struct vec *x, const struct vec *y);

/**
 * Calcule la distance entre deux points
 *
 * @param   const struct vec        *a    Premier point de la droite
 * @param   const struct vec        *b    Second point de la droite
 * @return  double                        Distance entre a et b
 */
double distance(const struct vec *a, const struct vec *b);

/**
 * Calcule la distance minimum entre p et la droite (ab)
 *
 * @param   const struct vec        *a    Premier point de la droite
 * @param   const struct vec        *b    Second point de la droite
 * @param   const struct vec        *p    Autre point
 * @return  double                        Distance entre p et (ab)
 */
double distanceMin(const struct vec *a, const struct vec *b, const struct vec *p);

/**
 * Retourne la valeur max entre x et y
 *
 * @param   double                  x     Première valeur
 * @param   double                  y     Seconde valeur
 * @param   double                        Maximum
 */
double max(double x, double y);

/**
 * Retourne la valeur min entre x et y
 *
 * @param   double                  x     Première valeur
 * @param   double                  y     Seconde valeur
 * @param   double                        Minimum
 */
double min(double x, double y);

/**
 * Compare deux points selon leur abscisse
 * Retourne 0 pour même abscisse
 * Retourne < 0 pour le premier plus à gauche
 * Retourne > 0 pour le second plus à gauche
 *
 * @param   struct vec              *p1   Premier point
 * @param   struct vec              *p2   Second point
 * @param   const void              *ctx  Doit être NULL (ignoré dans la fonction)
 * @return  int                           Entier de retour
 */
int compa_abscisses(const struct vec *p1, const struct vec *p2, const void *ctx);

/**
 * Calcule le carre d'un nombre
 *
 * @param   double                  x     Nombre réel
 * @return  double                        Carré de ce nombre
 */
double carre(double x);

#endif
