#include <array>
#include <algorithm>
#include <deque>
#include <iostream>
#include <cassert>
#include "meta.hh"

template <unsigned int COMPONENTS_SIZE>
unsigned comp_man_dist(std::array<struct component_p, COMPONENTS_SIZE> cmpt, unsigned index)
{
  unsigned ret = 0;
  for(auto i : cmpt[index].neighbours)
  {
    // printf("i: %u, x: %u, y: %u, x: %u, y: %u\n", i, cmpt.posx, cmpt.posy, cmpt.components[i]->posx, cmpt.components[i]->posy);
    ret += manahtan_dist(cmpt[index].posx, cmpt[index].posy, cmpt[i].posx, cmpt[i].posy);
  }
  return ret;
}

template <unsigned int COMPONENTS_SIZE>
int aggregated_comp_man_dist(std::array<struct component_p, COMPONENTS_SIZE>components)
{
  unsigned dist = 0;
  for(unsigned i = 0; i < COMPONENTS_SIZE; i++)
    //printf("dist: %u, i: %u\n", dist, i);
    dist += comp_man_dist<COMPONENTS_SIZE>(components, i);
  return dist;
}

template <unsigned int COMPONENTS_SIZE>
std::array<struct component_p, COMPONENTS_SIZE> arr_to_vec_component(struct component components[])
{
  std::array<struct component_p, COMPONENTS_SIZE> res;

  for (unsigned int i = 0; i < COMPONENTS_SIZE; i++)
  {
    res[i].posx = components[i].posx;
    res[i].posy = components[i].posy;

    for (unsigned int j = 0; j < components[i].links_nb; j++)
    {
      assert(components[i].components[j]);
      res[i].neighbours.push_back((components[i].components[j] - components));
    }
  }

  return res;
}

template <unsigned int COMPONENTS_SIZE>
std::array<struct component_p, COMPONENTS_SIZE> tabu_search(std::array<struct component_p, COMPONENTS_SIZE> components, unsigned max_tabu_size)
{
  auto sBest = components;
  std::deque<std::array<struct component_p, COMPONENTS_SIZE>> tabuList;
  tabuList.push_back(sBest);

  while (true)
  {
    int old_dist = aggregated_comp_man_dist<COMPONENTS_SIZE>(components);
    for (unsigned pos1 = 0; pos1 < COMPONENTS_SIZE; pos1++)
      for (unsigned pos2 = 0; pos2 < COMPONENTS_SIZE; pos2++)
      {
        if (pos1 == pos2)
          continue;

        swap(&components[pos1], &components[pos2]);

        int aggregated_dist = aggregated_comp_man_dist<COMPONENTS_SIZE>(components);

        if (std::find(tabuList.begin(), tabuList.end(), components) != tabuList.end() // In Tabu list
            || aggregated_dist > old_dist)
          swap(&components[pos1], &components[pos2]); // Rollback
        else
          old_dist = aggregated_dist;
      }

    if (old_dist < aggregated_comp_man_dist<COMPONENTS_SIZE>(sBest))
      sBest = components;
    tabuList.push_back(components);
    if (tabuList.size() > max_tabu_size)
      tabuList.pop_front();
  }

  return sBest;
}

