/* display.c */

#include <stdio.h>

#include "majrogue.h"

void display_draw_dungeon(void)
{
  for (int i = 0; i < DUN_SIZE; i++)
  {
    for (int j = 0; j < DUN_SIZE; j++)
    {
      putchar(maptiles[i][j] == WALL ? '#' : '.');
    }
    putchar('\n');
  }
  putchar('\n');
}