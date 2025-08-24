#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#include <stdio.h>

#include "majrogue.h"

char running_state[256];

static void rnum_init(void)
{
	time_t t = time(NULL);
	t ^= (getuid() << 16) | (getpid() & 0xFFFF);
#ifdef DEBUG
	t = 1234;
#endif
	initstate(t, running_state, 256);
}

/* ANYTHING TO THE POWER OF 0 EQUALS 1 */

int main(void)
{
  rnum_init();
	display_init();

	dungeon_generate();

	ncurses_display_draw_world();

	input_wait();

	player_init();

	display_shutdown();

	printf("%s", you.name);

  return 0;
}
