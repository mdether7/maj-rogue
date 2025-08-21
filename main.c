#include "majrogue.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

char running_state[256];
static void rnum_init(void)
{
	time_t t = time(NULL);
	t ^= (getuid() << 16) | (getpid() & 0xFFFF);
	initstate(t, running_state, 256);
}

/* ANYTHING TO THE POWER OF 0 EQUALS 1 */

int main(void)
{
  rnum_init();

  


  return 0;
}
