/* dungen.c */

#include <stdbool.h>
#include <string.h>

#include "majrogue.h"

enum tile_types maptiles[DUN_SIZE][DUN_SIZE]; /* stores tiles data of dungeon */

#define UNUSED_ROOM_CELL 99 /* sentinel value to keep the qsort order right */

typedef struct { /* should be internal to dungen.c */
  int x, y;
  int cx, cy;
  int order;
  bool used;
} room_cell;

static room_cell room_cells[DUN_CELL_NUMBER]; /* array internal to dungen */

static void reset_room_cells(void);

int generate_dungeon(void)
{
  memset(maptiles, WALL, sizeof(maptiles)); /* fills the maptiles with walls */
}

static void reset_room_cells(void)
{
  int count = 0;
  for (int i = 0; i < DUN_SIZE; i+=DUN_ROOM_SIZE)
  {
    for (int j = 0; j < DUN_SIZE; j+=DUN_ROOM_SIZE)
    {
      room_cells[count++] = (room_cell){i, j, 0, 0, UNUSED_ROOM_CELL, false};
    }
  }
}

