#include "meta.h"
#include "draw.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

int main(int argc, char ** strargs)
{
  srand(time(NULL));
  sdlinit();
  //initial temperature and temperature are user defined
  double temp = 0.2;
  double temp_step = 0.01;
  unsigned components_size = 36;
  struct component* components[36];
  simulated_annealing(components, components_size, temp, temp_step);
  SDL_Quit();
  return EXIT_SUCCESS;
}
