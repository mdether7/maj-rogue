/* player.c */

#include "majrogue.h"

#include <stdio.h>

struct player you;

void player_init(void)
{
  input_get_string(you.name, sizeof(you.name) - 1); /* minus one to save last char to '\0 */
  you.gold = 0;
  you.y = 0; /* not placed on map yet */
  you.x = 0;
}