#include <stdlib.h>
#include <SDL2/SDL.h>

#include "meta.h"

unsigned manahtan_dist(unsigned xa, unsigned ya, unsigned xb, unsigned yb)
{
  return abs(xb - xa) + abs(yb - ya);
}

unsigned comp_man_dist(struct component *cmpt)
{
  unsigned ret = 0;
  for(unsigned i = 0; i < cmpt->links_nb; i++)
    ret += manahtan_dist(cmpt->posx, cmpt->posy, cmpt->components[i]->posx, cmpt->components[i]->posy);
  return ret;
}

void swap(struct component* cmpt1, struct component* cmpt2)
{
  unsigned tmp = cmpt1->posx;
  cmpt1->posx = cmpt2->posx;
  cmpt2->posx = tmp;
  tmp = cmpt1->posy;
  cmpt1->posy = cmpt2->posy;
  cmpt2->posy = tmp;
}

int aggregated_comp_man_dist(struct component* components[], unsigned components_size)
{
  unsigned dist = 0;
  for(unsigned i = 0; i < components_size; i++)
    dist += comp_man_dist(components[i]);
  return dist;
}

void simulated_annealing(struct component* components[], unsigned components_size)
{
  unsigned max_iter = 123;
  unsigned min_energy = 200;
  unsigned energy = 700;
  unsigned iter = 0;
  unsigned prev_dist = 0;
  //SDL_Surface *box_arr[components_size];

  while(iter < max_iter && energy > min_energy)
  {
    energy--;
    iter++;

    unsigned pos1 = rand() % components_size;
    unsigned pos2 = rand() % components_size; //TODO: do not swap same pos

    swap(components[pos1], components[pos2]);

    int new_dist = aggregated_comp_man_dist(components, components_size);

    if(new_dist > prev_dist) // TODO: probas
      swap(components[pos1], components[pos2]);
  }
}


