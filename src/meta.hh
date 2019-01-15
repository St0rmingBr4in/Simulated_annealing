#pragma once
#include <vector>
#include <array>

struct component
{
  unsigned posx;
  unsigned posy;
  unsigned links_nb;
  struct component* components[4];
};

struct component_p
{
  unsigned posx;
  unsigned posy;
  std::vector<unsigned> neighbours;

  bool operator==(const struct component_p& b) const
  {
    return (posx == b.posx && posy == b.posy && neighbours == b.neighbours);
  }
};

template <unsigned int COMPONENTS_SIZE>
std::array<struct component_p, COMPONENTS_SIZE> arr_to_vec_component(struct component components[]);

template <unsigned int COMPONENTS_SIZE>
std::array<struct component_p, COMPONENTS_SIZE> tabu_search(std::array<struct component_p, COMPONENTS_SIZE> components, unsigned max_tabu_size);

void swap(struct component_p* cmpt1, struct component_p* cmpt2);

unsigned manahtan_dist(int xa, int ya, int xb, int yb);
unsigned comp_man_dist(struct component cmpt);
void swap(struct component* cmpt1, struct component* cmpt2);
int aggregated_comp_man_dist(struct component components[], unsigned components_size);
void simulated_annealing(struct component components[], unsigned component_size, unsigned max_iteration, double temp, double temp_step, unsigned energy_target);
unsigned get_delta_e(struct component components[], unsigned component_size);
int proba(unsigned delta_E, double temp);
double get_initial_temperature(double temp, unsigned delta_e);

#include "meta.hxx"
