/* display.c */

#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <stddef.h>

#include "majrogue.h"

static WINDOW* world_window;
static PANEL* world_panel;

int display_map_update;

static int get_terrain_char(enum tile_type tile);

int display_init(void)
{
  initscr();
  curs_set(0);
  noecho();
  cbreak();
  world_window = newwin(9, 17, 0, 0); /* 9 rows, 17 columns */
  world_panel = new_panel(world_window);
  wclear(world_window);
  display_map_update = TRUE;
  update_panels();
  doupdate();
  return 0;
}

void display_shutdown(void)
{
  del_panel(world_panel);
  world_panel = NULL;
  delwin(world_window);
  world_window = NULL;
  endwin();
}

void display_draw_world(void)
{
  wclear(world_window);

  for (int i = 0; i < DUN_SIZE; i++)
  {
    for (int j = 0; j < DUN_SIZE; j++)
    {
      mvwaddch(world_window, i, j, get_terrain_char(maptiles[i][j]));
    }
  }

  update_panels();
  doupdate();
}

static int get_terrain_char(enum tile_type tile)
{
  switch (tile)
  {
    case FLOOR: return '.';
    case WALL: return '#';
    case DOOR: return '+';
    default: return '?';
  }
}

void input_get_string(char* buffer, size_t length)
{
  echo();
  curs_set(1);

  buffer[0] = '\0';
  mvwgetnstr(world_window,0, 0, buffer, length);

  curs_set(0);
  noecho();
}

enum game_cmd get_command(void)
{
  
}

void input_wait(void)
{
  getch();
}

