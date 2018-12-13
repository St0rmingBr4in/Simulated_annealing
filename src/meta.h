#pragma once

struct component
{
  unsigned posx;
  unsigned posy;
  unsigned links_nb;
  struct component* components[4];
};

unsigned manahtan_dist(unsigned xa, unsigned ya, unsigned xb, unsigned yb);
unsigned comp_man_dist(struct component cmpt);
void swap(struct component* cmpt1, struct component* cmpt2);
int aggregated_comp_man_dist(struct component components[], unsigned components_size);
void simulated_annealing(struct component components[], unsigned component_size, unsigned temp, unsigned temp_step);
unsigned get_delta_e(struct component components[], unsigned component_size);
int proba(unsigned delta_E, double temp);
double get_initial_temperature(double temp, unsigned delta_e);
