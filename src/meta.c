#include <stdlib.h>
#include <SDL2/SDL.h>

#include "meta.h"

unsigned manahtan_dist(unsigned xa, unsigned ya, unsigned xb, unsigned yb)
{
  return abs(xb - xa) + abs(yb - ya);
}

unsigned comp_man_dist(struct component cmpt)
{
  unsigned ret = 0;
  for(unsigned i = 0; i < cmpt.links_nb; i++)
    ret += manahtan_dist(cmpt.posx, cmpt.posy, cmpt.components[i]->posx, cmpt.components[i]->posy);
  return ret;
}

void swap(struct component* cmpt1, struct component* cmpt2)
{
  if(cmpt1 == cmpt2)
    return;

  unsigned tmp = cmpt1->posx;
  cmpt1->posx = cmpt2->posx;
  cmpt2->posx = tmp;
  tmp = cmpt1->posy;
  cmpt1->posy = cmpt2->posy;
  cmpt2->posy = tmp;
}

int aggregated_comp_man_dist(struct component components[], unsigned components_size)
{
  unsigned dist = 0;
  for(unsigned i = 0; i < components_size; i++)
    dist += comp_man_dist(components[i]);
  return dist;
}

unsigned get_delta_e(struct component components[], unsigned component_size)
{
	int prev_man_dist = 0;
	for(unsigned i = 0; i < component_size; i++)
		prev_man_dist += comp_man_dist(components[i]);
	prev_man_dist /= 2;

	for(unsigned i = 0; i < 100; i++)
		swap(&components[rand() % component_size], &components[rand() % component_size]);

	int actual_man_dist = 0;
	for(unsigned i = 0; i < component_size; i++)
		actual_man_dist += comp_man_dist(components[i]);
	actual_man_dist /= 2;

	return abs(actual_man_dist - prev_man_dist);
}

int proba(unsigned delta_E, double temp)
{
	double r = (rand() % 100) / 100;
	return r <= exp(-(delta_E/temp));  
}

double get_initial_temperature(double temp, unsigned delta_e)
{
	return -delta_e/log(temp);
}

void simulated_annealing(struct component components[], unsigned components_size, unsigned temp, unsigned temp_step)
{
  unsigned max_iter = 123;
  unsigned min_energy = 200;
  unsigned energy = 700;
  unsigned iter = 0;
  unsigned prev_dist = 50000;
  //SDL_Surface *box_arr[components_size];

  unsigned delta_e = get_delta_e(components, components_size);
  temp = get_initial_temperature(temp, temp_step);

  while(iter < max_iter && energy > min_energy)
  {

    unsigned pos1 = rand() % components_size;
    unsigned pos2 = rand() % components_size;

    if(pos1 != pos2)
    {
      swap(&components[pos1], &components[pos2]);

      int new_dist = aggregated_comp_man_dist(components, components_size);

      if(new_dist > prev_dist || !proba(delta_e, temp))
        swap(&components[pos1], &components[pos2]);

      prev_dist = new_dist;

      iter++;
      temp -= temp_step;
    }
  }
}


