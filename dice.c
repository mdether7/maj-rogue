/* dice.c */

#include<stdlib.h>

#include"majrogue.h"

int dice_multiple(int count, int sides)
{
  int total = 0;
  for ( ; count > 0; count--) {
    total += dice(sides);
  }
  return total;
}

int dice_zero_multiple(int count, int sides)
{
  int total = 0;
  for ( ; count > 0; count--) {
    total += dice_zero(sides);
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

int dice_zero(int sides)
{
  int rval;
  int limit;
  
  limit = RAND_MAX - (RAND_MAX % sides);
  while ( (rval = rand()) >= limit );

  return rval % sides;
}

int rand_range(int min, int max)
{
  return min + dice_zero(max - min + 1);
}