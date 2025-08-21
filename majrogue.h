/* majrogue.h */
#ifndef MAJROGUE_H
#define MAJROGUE_H

#include <stdint.h>

/* XXX Defines */
#define DUN_SIZE 32 /* Whole dungeon is 32 x 32 = 1024 tiles */
#define DUN_ROOM_SIZE 8 /* Each "room cell" is 8 X 8 = 16 room tiles */
#define DUN_TOTAL_CELLS ((DUN_SIZE / DUN_ROOM_SIZE) * (DUN_SIZE / DUN_ROOM_SIZE))

#define MIN_ROOM_COUNT 4
#define MAX_ROOM_COUNT 8

/* XXX Enums */
enum tile_type {
  FLOOR = 0, WALL
};

enum room_type {
  ROOM_START = 0, ROOM_CAVE, ROOM_CROSS, ROOM_RECT, ROOM_SQUARE, ROOM_TOTAL
};

/* XXX Structs */
/* struct Player */
struct player {
  char name[17]; /* Max name lenght 16, here space included for '/0' */
  int y; /* y-coord */
  int x; /* x-coord */
  int gold;
};

struct room {
  enum tile_type layout[DUN_ROOM_SIZE][DUN_ROOM_SIZE];
};

/* XXX player.c */
extern void player_init(void);

/* XXX map.c */
extern enum tile_type maptiles[DUN_SIZE][DUN_SIZE];
extern int map_init(void);

/* XXX display.c */
extern void display_draw_dungeon(void);

/**
 * 
 * 
 * 
 * 
 * 
 */

/* XXX rooms.c */
extern struct room room_templates[ROOM_TOTAL];

/* XXX dungen.c */
extern int dungeon_generate(void);

/**
 * 
 * 
 * 
 * 
 * 
 */

/* XXX dice.c */
extern int dice(int sides); /* dice range 1 to SIDES */
extern int dice_zero(int sides); /* dice range 0 to SIDES-1 */
extern int dice_multiple(int count, int sides);
extern int dice_zero_multiple(int count, int sides); /* [[MAYBE_UNUSED]] */ 
extern int rand_range(int min, int max);

#endif /* MAJROGUE_H */
