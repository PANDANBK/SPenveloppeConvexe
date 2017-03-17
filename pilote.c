#include "hull.h"
#include "jarvis.h"
#include "graham.h"

int main()
{
  setbuf(stdout, NULL);

  char buffer[BUFSIZE];
  fgets(buffer, BUFSIZE, stdin);

  size_t count = strtol(buffer, NULL, 10);

  // Vecset qu'on utilisera
  struct vecset ensemble;
  vecset_create(&ensemble);

  for(size_t i = 0; i < count; ++i)
  {
    struct vec p;

    fgets(buffer, BUFSIZE, stdin);

    char *endptr = buffer;
    p.x = strtod(endptr, &endptr);
    p.y = strtod(endptr, &endptr);

    vecset_add(&ensemble, p);
  }

  struct vecset sortie;
  jarvis_march(&ensemble, &sortie);
  // graham_scan(&ensemble, &sortie);

  printf("%zu\n", sortie.size);
  for(size_t i = 0; i < sortie.size; i++)
  {
    printf("%f %f\n", sortie.data[i].x, sortie.data[i].y);
  }

  vecset_destroy(&sortie);
  vecset_destroy(&ensemble);

  return 0;
}
