#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

#include <stdio.h>

#include "majrogue.h"

char running_state[256];

static void rnum_init(void);
static void menu(enum game_state* state);
static void game(enum game_state* state);
// static void new_game(void);
// static int save_game(void);

static void rnum_init(void)
{
	time_t t = time(NULL);
	t ^= (getuid() << 16) | (getpid() & 0xFFFF);
#ifdef DEBUG
	t = 1234;
#endif
	initstate(t, running_state, 256);
}

// static int save_game(void)
// {
// 	FILE* save_file;
// 	save_file = fopen("save.sav", "wb");
// 	if (!save_file) {
// 		perror("fopen");
// 		return 1;
// 	}

// 	size_t bytes_written;
// 	bytes_written = fwrite(maptiles, sizeof(maptiles), 1, save_file);
// 	//bytes_written = fwrite(maptiles, sizeof(enum tile_type), sizeof(maptiles) ,save_file);
// 	if (bytes_written != 1) {
// 		printf("%ld", bytes_written);
// 		perror("fwrite");
// 		return 1;
// 	}
// 	fclose(save_file);

// 	return 0;
// }

/* ANYTHING TO THE POWER OF 0 EQUALS 1 */

// static void new_game(void)
// {
// 	player_init();
// }

static void menu(enum game_state* state)
{
	display_draw_menu();
	enum menu_cmd cmd = get_menu_cmd();
	switch (cmd)
	{
		case MENU_SELECT: break;
		case MENU_GO_UP: break;
		case MENU_GO_DOWN: break;
		case MENU_QUIT: break;
		case MENU_RETURN_GAME: break;
		default: /* something unexpected happened */
			display_shutdown();
			abort();
		break;
	}
}

static void game(enum game_state* state)
{

}

int main(void)
{
	display_init();

	enum game_state state = STATE_MENU;
	while (state != STATE_OVER)
	{
		switch (state)
		{
			case STATE_MENU: menu(&state); break;
			case STATE_GAME: game(&state); break;
			case STATE_OVER: break;
			default: abort(); /* something wierd happend */
		}
	}

	rnum_init();

	dungeon_generate();

	display_draw_world();

	display_shutdown();
  return 0;
}
