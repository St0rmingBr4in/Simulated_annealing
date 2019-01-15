#include "draw.hh"
#include "latexdraw.hh"
/* -*-ePiX-*- */
#include "epix.h"
using namespace ePiX;

const double MAX(1);

P F(double u, double v)
{
  return sph(1, u, v);
}

template<typename N>
latexdrawing<N>::latexdrawing()
{
}

template <>
void latexdrawing<std::array<struct component_p, 36>>::draw(std::array<struct component_p, 36> components)
{
  picture(P(-1,-1), P(6,6), "5x5cm");

  begin();

  border(Black(), "1pt");

  font_size("tiny");

  for(unsigned i = 0; i < 36; i++)
  {

    std::ostringstream out;
    out << i;

    label(P(components[i].posx, components[i].posy), out.str());
    for (auto j : components[i].neighbours)
      arrow(P(components[i].posx, components[i].posy), P(components[j].posx, components[j].posy));

  }

  end();
}

template <>
void latexdrawing<struct component[36]>::draw(struct component components[36])
{
  picture(P(-1,-1), P(6,6), "5x5cm");

  begin();

  border(Black(), "1pt");

  font_size("tiny");

  for(unsigned i = 0; i < 36; i++)
  {

    std::ostringstream out;
    out << i;

    label(P(components[i].posx, components[i].posy), out.str());
    for (unsigned j = 0; j < components[i].links_nb; j++)
      arrow(P(components[i].posx, components[i].posy), P(components[i].components[j]->posx, components[i].components[j]->posy));

  }

  end();
}
