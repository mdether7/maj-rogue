#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

#include <stdio.h>

#include "majrogue.h"

char running_state[256];

static void rnum_init(void);
static void new_game(void);
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

static void new_game(void)
{
	player_init();
}

int main(void)
{
	display_init();

	enum game_state state = MENU;
	int quit = 0;
	while (!quit)
	{
		switch (state)
		{
			case MENU: break;
			case GAME: break;
			default: abort(); /* shoudl not ever happen*/
		}
	}

	rnum_init();

	dungeon_generate();

	display_draw_world();

	display_shutdown();
  return 0;
}
