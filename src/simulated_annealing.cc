#include "meta.hh"
#include "SDLdraw.hh"


#include <stdlib.h>
#include <SDL2/SDL.h>
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

/* -*-ePiX-*- */
#include "epix.h"
using namespace ePiX;

const double MAX(1);

P F(double u, double v)
{
  return sph(1, u, v);
}

int main()
{
  srand(time(NULL));
  struct component components[36];
  fillAndShuffle(components);

  auto test = arr_to_vec_component<36>(components);

  SDLdrawing<decltype(test)> t;
  t.draw(test);

  // for (auto i : test)
  // {
  //   std::cout << "x: " << i.posx << ", y: " << i.posy << ", neigh: ";
  //   for (int j : i.neighbours)
  //   {
  //     std::cout << j << ", ";
  //   }
  //   std::cout << std::endl;
  // }

  tabu_search<36, SDLdrawing<decltype(test)>>(test, 10000, 100, t);
  simulated_annealing(components, 36, 7000, 1, 0.01, 200);

}



/*
void draw(struct component components[36])
{

  picture(P(0,0), P(20,20), "15x15cm");

  begin();

  // uncomment and permute these lines
  // crop_ellipse();
  // backing(Cyan());
  //border(Black(), "1pt");

  font_size("tiny");
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
    {
      std::ostringstream out;  
      out << i << "," << j;
      label(P(2 * i, 2 * j), out.str());
    }
  end();
  }

  */
  /*
  picture(P(0,0),P(5,1), "5 x 1in");

  begin();

  pst_format();
  domain coarse(P(0,0), P(0.5, 1), mesh(6,12), mesh(60,60));
  domain fine(P(0,0), P(0.5, 1), mesh(15,30), mesh(60,60));

  revolutions();
  ePiX::camera.at(P(5, 4, 3));

  fill(White());

  nofill(); // fill color set -> flat shading
  screen scr1(P(-1,-1), P(1,1));
  activate(scr1);
  surface(F, coarse);

  screen scr2(P(-1,-1), P(1,1));
  activate(scr2);
  surface(F, fine);

  fill();
  screen scr3(P(-1,-1), P(1,1));
  activate(scr3);
  surface(F, coarse);

  screen scr4(P(-1,-1), P(1,1));
  activate(scr4);
  surface(F, fine);

  inset(scr1, P(0,0), P(1,1));
  inset(scr2, P(1.25,0), P(2.25,1));
  inset(scr3, P(2.5,0), P(3.5,1));
  inset(scr4, P(3.75,0), P(4.75,1));

  end();
}
*/
