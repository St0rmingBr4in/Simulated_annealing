#pragma once

struct component
{
  unsigned posx;
  unsigned posy;
  unsigned links_nb;
  struct component* components[4];
};

unsigned manahtan_dist(int xa, int ya, int xb, int yb);
unsigned comp_man_dist(struct component cmpt);
void swap(struct component* cmpt1, struct component* cmpt2);
int aggregated_comp_man_dist(struct component components[], unsigned components_size);
void simulated_annealing(struct component components[], unsigned component_size, unsigned max_iteration, double temp, double temp_step, unsigned energy_target);
unsigned get_delta_e(struct component components[], unsigned component_size);
int proba(unsigned delta_E, double temp);
double get_initial_temperature(double temp, unsigned delta_e);
