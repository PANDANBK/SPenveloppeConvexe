#ifndef DEF_GRAHAM
#define DEF_GRAHAM

#include <math.h>
#include "hull.h"

#define PI 3.1415

/**
 * Implémente le parcours de Graham.
 *
 * @param   const struct vecset     *in   Ensemble d'entrée
 * @param   const struct vecset     *in   Ensemble de sortie
 */
void graham_scan(const struct vecset *in, struct vecset *out);

/**
 * Compare deux points selon leur ordonnée
 * Retourne 0 pour autant à gauche (même ordonnée et même abscisse)
 * Retourne < 0 pour le premier plus en bas (ou autant en bas mais plus à gauche)
 * Retourne > 0 pour le second plus en bas (ou autant en bas mais plus à gauche)
 *
 * @param struct vec *p1    Premier point
 * @param struct vec *p2    Second point
 * @param const void *ctx   Doit être NULL (ignoré dans la fonction)
 * @return int              Entier de retour
 */
int compa_lowest(const struct vec *p1, const struct vec *p2, const void *ctx);

/**
 * Compare deux points selon leur angle avec l'axe des abscisses relativement à B
 * Retourne 0 même angle
 * Retourne < 0 pour le premier plus petit angle
 * Retourne > 0 pour le second plus petit angle
 *
 * @param struct vec *p1    Premier point
 * @param struct vec *p2    Deuxième point
 * @param const void *ctx   Troisème point
 * @return int              Entier de retour
 */
int compa_angle(const struct vec *p1, const struct vec *p2, const void *ctx);

#endif
