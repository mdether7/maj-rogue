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

static room_cell room_cells[DUN_TOTAL_CELLS]; /* array internal to dungen */

static void reset_room_cells(void);
static int comp_qsort(const void* x, const void* y);

int generate_dungeon(void)
{
  memset(maptiles, WALL, sizeof(maptiles)); /* fills the maptiles with walls */
  reset_room_cells();

  /* randomize the number of rooms that will be created */
  int total_rooms = rand_range(MIN_ROOM_COUNT, MAX_ROOM_COUNT);

  /* Choose random room cell for starting room  */
  int random_cell = zero_dice(DUN_TOTAL_CELLS);

  room_cells[random_cell].used = true; /* first room will always "fit" */
  room_cells[random_cell].order = 1; /* track order of creation for later iteration  */

  for (int room_x = 0 ;room_x < DUN_ROOM_SIZE; room_x++)
  {
    for (int room_y = 0 ;room_y < DUN_ROOM_SIZE; room_y++)
    {
      maptiles[room_x + room_cells[random_cell].x]
              [room_y + room_cells[random_cell].y] =
      room_templates[ROOM_START].layout[room_x][room_y];
    }
  }

  total_rooms--; /* after we create starting room */
  int room_index = 2;

  while (total_rooms) {

    random_cell = zero_dice(DUN_TOTAL_CELLS);

    if (room_cells[random_cell].used) {
      continue;
    }

    room_cells[random_cell].used = true;

    int random_room = dice(ROOM_TOTAL - 1);
    for (int room_x = 0; room_x < DUN_ROOM_SIZE; room_x++)
    {
      for (int room_y = 0; room_y < DUN_ROOM_SIZE; room_y++)
      {
        maptiles[room_x + room_cells[random_cell].x]
                [room_y + room_cells[random_cell].y] = 
        room_templates[random_room].layout[room_x][room_y];
      }
    }

    total_rooms--;
    room_cells[random_cell].order = room_index++;
  }
  /**
   * at the end sort room_cells in order of creation
   * for later iteration (rhymes:D) 
   */
  qsort(room_cells, DUN_TOTAL_CELLS, sizeof(room_cell), comp_qsort);
  
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

static int comp_qsort(const void* x, const void* y)
{
  room_cell* cellx = (room_cell*)x;
  room_cell* celly = (room_cell*)y;
  
  return cellx->order - celly->order;
}

