/* display.c */

#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <stddef.h>

#include "majrogue.h"

static WINDOW* world_window;
static PANEL* world_panel;

static WINDOW* menu_window;
static PANEL* menu_panel;

int display_map_update;
int display_menu_update;

static int get_terrain_char(enum tile_type tile);

int display_init(void)
{
  initscr();
  curs_set(0);
  noecho();
  cbreak();
  menu_window = newwin(20, 20, 0, 0);
  world_window = newwin(9, 17, 0, 0); /* 9 rows, 17 columns */
  menu_panel = new_panel(menu_window);
  world_panel = new_panel(world_window);
  wclear(menu_window);
  wclear(world_window);
  display_map_update = TRUE;
  display_menu_update = TRUE;
  update_panels();
  doupdate();
  return 0;
}

void display_shutdown(void)
{
  del_panel(menu_panel);
  menu_panel = NULL;
  delwin(menu_window);
  menu_window = NULL;
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

void display_draw_menu(void)
{
  
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

enum game_cmd get_game_cmd(void)
{
  return GAME_MOVE_EAST;
}

enum menu_cmd get_menu_cmd(void)
{
  return MENU_GO_UP;
}

void input_wait(void)
{
  getch();
}

