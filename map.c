/* map.c */

#include <string.h>

#include "majrogue.h"

enum tile_type maptiles[DUN_SIZE][DUN_SIZE];

extern int map_init(void)
{
  memset(maptiles, 0, sizeof(maptiles));
  return 0;
}