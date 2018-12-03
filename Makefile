CFLAGS=-O3 -Wall -Werror -pedantic -g $(shell sdl2-config --cflags)
LDFLAGS=-lSDL2
EXEC=simulated_annealing
OBJS=meta.o simulated_annealing.o draw.o

VPATH=src

all: ${EXEC}

${EXEC}: ${OBJS}

clean:
	$(RM) -fr *.o

mrproper: clean
	$(RM) -fr ${EXEC}
