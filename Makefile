# My first ever Makefile (mdether7)
GAME= majrogue
CC= cc
OPT= -O0
CFLAGS= -c -g -Wall -Wstrict-prototypes -Wwrite-strings -Wmissing-prototypes -Werror
LINKFLAGS= -g -lncurses -lpanel
OBJS= dice.o main.o player.o dungen.o

all: $(GAME)

$(GAME): $(OBJS)
	$(CC) $(OBJS) $(LINKFLAGS) -o $(GAME)

%.o: %.c # Wildcard variables (where % is a wildcard wich means anything!)
	$(CC) $(CFLAGS) $(OPT) $<

main.o: main.c majrogue.h

dice.o: dice.c majrogue.h

dungen.o: dungen.c majrogue.h

player.o: player.c majrogue.h

preproc:
	$(CC) -E -o $(GAME).preproc dice.c

archive: clean
	tar zcfv $(GAME).tar.gz --exclude='*.tgz' *

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(GAME) *.preproc

.PHONY: all clean archive #don't confuse with files named all/clean etc.
