#include "meta.h"
#include "draw.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

void fillAndShuffle(struct component components[])
{
	for(unsigned x = 0; x < 6; x++)
		for(unsigned y = 0; y < 6; y++)
		{
			components[x + 6 * y].posx = x;
			components[x + 6 * y].posy = y;
		}

	draw(components);
/*
	for(unsigned i = 0; i < 1000; i++)
		swap(components[rand() % 36], components[rand() % 36]);
		*/
}


int main(int argc, char ** strargs)
{
	srand(time(NULL));
	sdlinit();
	//initial temperature and temperature are user defined
//	double temp = 0.2;
//	double temp_step = 0.01;
//	unsigned components_size = 36;
	struct component components[36];
	fillAndShuffle(components);
//	simulated_annealing(components, components_size, temp, temp_step);
	SDL_Quit();
	return EXIT_SUCCESS;
}
