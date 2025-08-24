/* display.c */

#include <stdio.h>

#include "majrogue.h"

void display_draw_dungeon(void)
{
  for (int i = 0; i < DUN_SIZE; i++)
  {
    for (int j = 0; j < DUN_SIZE; j++)
    {
      enum tile_type tile = maptiles[i][j];
      switch (tile)
      {
        case FLOOR: putchar('.'); break;
        case WALL: putchar('#'); break;
        case DOOR: putchar('+'); break;
        default: putchar('?'); break;
      }
    }
    putchar('\n');
  }
  putchar('\n');
}