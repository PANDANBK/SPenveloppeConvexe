#ifndef DEF_JARVIS
#define DEF_JARVIS

#include "hull.h"
#include <time.h>

/**
 * Implémente la marche de Jarvis
 *
 * @param   const struct vecset     *in   Ensemble d'entrée
 * @param   const struct vecset     *in   Ensemble de sortie
 */
void jarvis_march(const struct vecset *in, struct vecset *out);

/**
 * Tire un nombre aléatoire dans [min, max]
 *
 * @param   size_t                  min   Minimum
 * @param   size_t                  max   Maximum
 * @return  size_t                        Nombre aléatoire
 */
size_t aleat(size_t min, size_t max);

/**
 * Tire un point aléatoire dans l'ensemble
 *
 * @return  vec*                   Point aléatoire
 */
struct vec *vecset_random(const struct vecset *self);

/**
 * Compare deux points selon le plus à gauche.
 * Retourne 0 pour autant à gauche (même abscisse)
 * Retourne < 0 pour le premier plus à gauche
 * Retourne > 0 pour le second plus à gauche
 *
 * @param struct vec *p1    Premier point
 * @param struct vec *p2    Second point
 * @param const void *ctx   Doit être NULL (ignoré dans la fonction)
 * @return int              Entier de retour
 */
int compa_most_left(struct vec *p1, const struct vec *p2, const void *ctx);

#endif
