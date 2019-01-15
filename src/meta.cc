#include <cstdlib>
#include <deque>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <SDL2/SDL.h>
#include <cassert>

#include "draw.hh"
#include "meta.hh"

unsigned manahtan_dist(int xa, int ya, int xb, int yb)
{
  return abs(xb - xa) + abs(yb - ya);
}

unsigned comp_man_dist(struct component cmpt)
{
  unsigned ret = 0;
  for(unsigned i = 0; i < cmpt.links_nb; i++)
  {
    assert(cmpt.components[i]);
    // printf("i: %u, x: %u, y: %u, x: %u, y: %u\n", i, cmpt.posx, cmpt.posy, cmpt.components[i]->posx, cmpt.components[i]->posy);
    ret += manahtan_dist(cmpt.posx, cmpt.posy, cmpt.components[i]->posx, cmpt.components[i]->posy);
  }
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

void swap(struct component_p* cmpt1, struct component_p* cmpt2)
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
    //printf("dist: %u, i: %u\n", dist, i);
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
