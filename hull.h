#ifndef HULL_H
#define HULL_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 1024

/**
 * Vecteur (représente aussi les points)
 */
struct vec
{
  double x;
  double y;
};

/**
 * Calcule le produit scalaire de v1 et v2
 *
 * @param   const struct vec    *v1   Permier vecteur
 * @param   const struct vec    *v2   Second pointeur
 * @return  double                    Produit scalaire
 */
double dot(const struct vec *v1, const struct vec *v2);

/**
 * Calcule le produit vectoriel 2D des vecteurs P1P2 et P1P3
 *
 * @param   const struct vec    *p1   Premier point
 * @param   const struct vec    *p2   Deuxième point
 * @param   const struct vec    *p3   Troisième point
 * @return  double                    Produit vectoriel 2D
 */
double cross(const struct vec *p1, const struct vec *p2, const struct vec *p3);

/**
 * Indique si la suite de points p1 p2 p3 constitue un tournant à gauche
 *
 * @param   const struct vec    *p1   Premier point
 * @param   const struct vec    *p2   Deuxième point
 * @param   const struct vec    *p3   Troisième point
 * @return  bool                      Vrai si tournant à gauche
 */
bool is_left_turn(const struct vec *p1, const struct vec *p2, const struct vec *p3);

/**
 * Ensemble de points
 */
struct vecset
{
  struct vec *data;
  size_t size;
  size_t capacity;
};

/**
 * Création d'un ensemble de points vide
 *
 * @param   struct vecset     *self   Ensemble à créer
 */
void vecset_create(struct vecset *self);

/**
 * Destruction d'un ensemble de points
 *
 * @param   struct vecset     *self   Ensemble à détruire
 */
void vecset_destroy(struct vecset *self);

/**
 * Ajoute le point p à l'ensemble self
 *
 * @param   struct vecset     *self   Ensemble de points
 * @param   struct vec        p       Point à ajouter
 */
void vecset_add(struct vecset *self, struct vec p);

typedef int (*comp_func_t)(const struct vec *p1, const struct vec *p2, const void *ctx);

/**
 * Renvoie le maximum d'un ensemble de points suivant une fonction de comparaison donnée
 *
 * @param   const struct vecset *self   Nuage de points
 * @param   comp_func_t         func    Fonction de comparaison
 * @param   const void          *ctx
 * @return  const struct vec*           Maximum de l'ensemble de points self
 */
const struct vec *vecset_max(const struct vecset *self, comp_func_t func, const void *ctx);

/**
 * Renvoie le minimum d'un ensemble de points suivant une fonction de comparaison donnée
 *
 * @param   const struct vecset *self   Nuage de points
 * @param   comp_func_t         func    Fonction de comparaison
 * @param   const void          *ctx
 * @return  const struct vec*           Minimum de l'ensemble de points self
 */
const struct vec *vecset_min(const struct vecset *self, comp_func_t func, const void *ctx);

/**
 * Trie l'ensemble de points suivant une fonction de comparaison donnée
 *
 * @param   const struct vecset *self   Nuage de points à trier
 * @param   comp_func_t         func    Fonction de comparaison
 * @param   const void          *ctx
 */
void vecset_sort(struct vecset *self, comp_func_t func, const void *ctx);

/**
 * Emplie un élément
 *
 * @param   struct vecset       *self   Nuage de points
 * @param   struct vec          p       Point à empiler
 */
void vecset_push(struct vecset *self, struct vec p);

/**
 * Dépile un élément
 *
 * @param   struct vecset       *self   Nuage de points
 */
void vecset_pop(struct vecset *self);

/**
 * Renvoie le premier élément de la pile
 *
 * @param   struct vecset       *self   Nuage de points
 * @return  const struct vec*           Deuxième élément de la pile
 */
const struct vec *vecset_top(const struct vecset *self);

/**
 * Renvoie le deuxième élément de la pile
 *
 * @param   struct vecset       *self   Nuage de points
 * @return  const struct vec*           Premier élément de la pile
 */
const struct vec *vecset_second(const struct vecset *self);

#endif
