#include "meta.hh"
#include "SDLdraw.hh"
#include "latexdraw.hh"


#include <stdlib.h>
#include <time.h>

void fillAndShuffle(struct component components[])
{
  for(unsigned x = 0; x < 6; x++)
    for(unsigned y = 0; y < 6; y++)
    {
      components[x + 6 * y].posx = x;
      components[x + 6 * y].posy = y;
      if(x != 0 && x != 5 && y != 0 && y != 5)
      {
        components[x + 6 * y].links_nb = 4;
        components[x + 6 * y].components[0] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[1] = &components[x + 1 + 6 * y];
        components[x + 6 * y].components[2] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[3] = &components[x - 1 + 6 * y];
      }
      else if(x == 0 && y == 0)
      {	
        components[x + 6 * y].links_nb = 2;
        components[x + 6 * y].components[0] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[1] = &components[x + 1 + 6 * y];
      }
      else if(x == 5 && y == 5)
      {	
        components[x + 6 * y].links_nb = 2;
        components[x + 6 * y].components[0] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[1] = &components[x - 1 + 6 * y];
      }
      else if(x == 0 && y == 5)
      {	
        components[x + 6 * y].links_nb = 2;
        components[x + 6 * y].components[0] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[1] = &components[x + 1 + 6 * y];
      }
      else if(x == 5 && y == 0)
      {	
        components[x + 6 * y].links_nb = 2;
        components[x + 6 * y].components[0] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[1] = &components[x - 1 + 6 * y];
      }
      else if(x > 0 && x < 5 && y == 0)
      {	
        components[x + 6 * y].links_nb = 3;
        components[x + 6 * y].components[0] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[1] = &components[x - 1 + 6 * y];
        components[x + 6 * y].components[2] = &components[x + 1 + 6 * y];
      }
      else if(x > 0 && x < 5 && y == 5)
      {	
        components[x + 6 * y].links_nb = 3;
        components[x + 6 * y].components[0] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[1] = &components[x - 1 + 6 * y];
        components[x + 6 * y].components[2] = &components[x + 1 + 6 * y];
      }
      else if(y > 0 && y < 5 && x == 0)
      {	
        components[x + 6 * y].links_nb = 3;
        components[x + 6 * y].components[0] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[1] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[2] = &components[x + 1 + 6 * y];
      }
      else if(y > 0 && y < 5 && x == 5)
      {	
        components[x + 6 * y].links_nb = 3;
        components[x + 6 * y].components[0] = &components[x + 6 * (y - 1)];
        components[x + 6 * y].components[1] = &components[x + 6 * (y + 1)];
        components[x + 6 * y].components[2] = &components[x - 1 + 6 * y];
      }

    }
  for(unsigned i = 0; i < 1000; i++)
    swap(&components[rand() % 36], &components[rand() % 36]);
  //	draw(components);
}


int main(int argc, char **argv)
{
  srand(time(NULL));
  struct component components[36];
  fillAndShuffle(components);

  if (argc == 1)
  {
    auto test = arr_to_vec_component<36>(components);
    latexdrawing<struct component [36]> t;
    t.draw(components);

    simulated_annealing(components, 36, 10000, 1, 0.01, 200, t);

    std::cout << "\\newpage" << std::endl;
    std::cout << "\\subsection{Recherche Tabu}" << std::endl;


    latexdrawing<decltype(test)> t2;
    t2.draw(test);

    tabu_search<36, latexdrawing<decltype(test)>>(test, 100000, 200, t2);
  }
  else if (std::string(argv[1]) == "simulated_annealing")
  {
    latexdrawing<struct component [36]> t;
    t.draw(components);

    simulated_annealing(components, 36, 10000, 1, 0.01, 200, t);
  }
  else if (std::string(argv[1]) == "tabu")
  {
    auto test = arr_to_vec_component<36>(components);

    latexdrawing<decltype(test)> t;
    t.draw(test);

    tabu_search<36, latexdrawing<decltype(test)>>(test, 100000, 200, t);
  }
  else
  {
    return EXIT_FAILURE;
  }
}
