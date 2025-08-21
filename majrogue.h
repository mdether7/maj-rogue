/* majrogue.h */

#ifndef MAJROGUE_H
#define MAJROGUE_H

#include <stdint.h>

/* XXX Defines */
#define DUN_SIZE 32 /* Whole dungeon is 32 x 32 = 1024 tiles */
#define DUN_ROOM_SIZE 8 /* Each "room cell" is 8 X 8 = 16 room tiles */

/* XXX typedefs */
typedef int8_t MAP_INT; /* just to keep the array sizes smaller */

/* XXX Structs */
/* struct Player */
struct player {
  char name[17]; /* Max name lenght 10, here space included for '/0' */
  int y; /* y-coord */
  int x; /* x-coord */
  int gold;
};

struct room {
  char layout[DUN_ROOM_SIZE][DUN_ROOM_SIZE];
};

enum tile_types {
  FLOOR = 0, WALL
};

enum room_types {
  ROOM_START = 0, ROOM_CAVE, ROOM_CROSS, ROOM_RECT, ROOM_SQUARE, ROOM_TOTAL
};

/* XXX player.c */
void player_init(void);

/* XXX dungen.c */
extern MAP_INT maptiles[DUN_SIZE][DUN_SIZE]; 

/* XXX dice.c */
extern int dice(int sides); /* dice range 1 to SIDES */
extern int zero_dice(int sides); /* dice range 0 to SIDES-1 */
extern int dice_multiple(int count, int sides);
extern int rand_range(int min, int max);
extern int zero_dice_multiple(int count, int sides); /* [[MAYBE_UNUSED]] */ 

#endif /* MAJROGUE_H */
