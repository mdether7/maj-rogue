/* dungen.c */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "majrogue.h"

typedef struct { /* should be internal to dungen.c */
  int x, y;
  int cx, cy;
  int order;
  // enum room_type type; NOTE(mdether7): That's great idea!
  bool used;
} room_cell;

static room_cell room_cells[DUN_TOTAL_CELLS]; /* array internal to dungen */

static void reset_room_cells(void);
static void fill_map_tiles(enum tile_type type);
static void connect_rooms(room_cell* room_first, room_cell* room_second);
static void place_doors(room_cell* room);
static void get_random_room_center(int room_x, int room_y,
                                   int* target_x, int* target_y);
static int comp_qsort(const void* x, const void* y);

int dungeon_generate(void)
{
  fill_map_tiles(WALL);
  reset_room_cells();

  /* randomize the number of rooms that will be created */
  int total_rooms = rand_range(MIN_ROOM_COUNT, MAX_ROOM_COUNT);
  int rooms_to_create = total_rooms; /* i need to cache the original count */

  /* Choose random room cell for starting room  */
  int random_cell = dice_zero(DUN_TOTAL_CELLS);

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

  rooms_to_create--; /* after we create starting room */
  int room_index = 2;

  while (rooms_to_create) {

    random_cell = dice_zero(DUN_TOTAL_CELLS);

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

    rooms_to_create--;
    room_cells[random_cell].order = room_index++; /* keep indexing */
  }

  /**
   * at the end sort room_cells in order of creation
   * for later iteration (rhymes:D) 
   */
  qsort(room_cells, DUN_TOTAL_CELLS, sizeof(room_cell), comp_qsort);

  /**
   * Now generate random center for each room from where
   * the corridors will start to be layed down
   */
  for (int room = 0; room < total_rooms; room++)
  {
    get_random_room_center( room_cells[room].x,
                            room_cells[room].y,
                            &room_cells[room].cx,
                            &room_cells[room].cy );
  }

  /**
   * now connect all the rooms with each other 
   * in order of creation so that all rooms get connected. 
   */
  for (int room = 0; room < total_rooms - 1; room++)
  {
    connect_rooms(&room_cells[room], &room_cells[room+1]);
  }

  place_doors(&room_cells[0]); /* TEMP */
  
  return 0;
}

static void connect_rooms(room_cell* room_first, room_cell* room_second)
{
  /* TODO(mdether7): Randomize L corridor placement */
  int x_dist = abs(room_first->cx - room_second->cx);
  int y_dist = abs(room_first->cy - room_second->cy);

  for (int tile = 0; tile <= x_dist; tile++)
  {
    if ( room_first->cx < room_second->cx )
    {
      maptiles[room_first->cx+tile][room_first->cy] = FLOOR;
    }
    else
    {
      maptiles[room_first->cx-tile][room_first->cy] = FLOOR;
    }
  }

  for (int tile = 0; tile <= y_dist; tile++)
  {
    if ( room_first->cy < room_second->cy )
    {
      maptiles[room_second->cx][room_second->cy-tile] = FLOOR;
    }
    else
    {
      maptiles[room_second->cx][room_second->cy+tile] = FLOOR;
    }
  }
}

static void place_doors(room_cell* room)
{
  (void)room;

}

static void fill_map_tiles(enum tile_type type)
{
  for (int x = 0; x < DUN_SIZE; x++)
  {
    for (int y = 0; y < DUN_SIZE; y++)
    {
      maptiles[x][y] = type;
    }
  }
}

static void get_random_room_center(int room_x, int room_y,
                                   int* target_x, int* target_y)
{
  int r = dice_zero(4);
  int count = 0;
  for (int i = 3; i < 5; i++)
  {
    for (int j = 3; j < 5; j++)
    {
      if ( r == count ) {
        *target_x = room_x + i;
        *target_y = room_y + j;
        return;
      }
      count++;
    }
  }
} 

static void reset_room_cells(void)
{
  int count = 0;
  for (int i = 0; i < DUN_SIZE; i+=DUN_ROOM_SIZE)
  {
    for (int j = 0; j < DUN_SIZE; j+=DUN_ROOM_SIZE)
    {
      room_cells[count++] = (room_cell){i, j, 0, 0, INT_MAX, false};
    }
  }
}

static int comp_qsort(const void* x, const void* y)
{
  room_cell* cellx = (room_cell*)x;
  room_cell* celly = (room_cell*)y;
  
  return cellx->order - celly->order;
}

