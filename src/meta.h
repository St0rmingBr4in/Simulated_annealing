#pragma once

struct component
{
  unsigned posx;
  unsigned posy;
  const char *name;
  unsigned links_nb;
  struct component* components[];
};

unsigned manahtan_dist(unsigned xa, unsigned ya, unsigned xb, unsigned yb);
unsigned comp_man_dist(struct component *cmpt);
void swap(struct component* cmpt1, struct component* cmpt2);
int aggregated_comp_man_dist(struct component* components[], unsigned components_size);
void simulated_annealing();

