/* dice.c */

#include"majrogue.h"
#include<stdlib.h>

int dice_multiple(int count, int sides)
{
  int total = 0;
  for ( ; count > 0; count--) {
    total += dice(sides);
  }
  return total;
}

int zero_dice_multiple(int count, int sides)
{
  int total = 0;
  for ( ; count > 0; count--) {
    total += zero_dice(sides);
  }
  return total;
}

int dice(int sides)
{
  int rval;
  int limit;
  
  limit = RAND_MAX - (RAND_MAX % sides);
  while ( (rval = rand()) >= limit );

  return rval % sides + 1;
}

int zero_dice(int sides)
{
  int rval;
  int limit;
  
  limit = RAND_MAX - (RAND_MAX % sides);
  while ( (rval = rand()) >= limit );

  return rval % sides;
}

int rand_range(int min, int max)
{
  return min + zero_dice(max - min + 1);
}