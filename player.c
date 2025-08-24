/* player.c */

#include "majrogue.h"

#include <stdio.h>

struct player you;

void player_init(void)
{
  // struct player p; //* local variable u IDIOT */
  input_get_string(you.name, sizeof(you.name));
}