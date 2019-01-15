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
  picture(P(0,0), P(20,20), "15x15cm");

  begin();

  // uncomment and permute these lines
  // crop_ellipse();
  // backing(Cyan());
  //border(Black(), "1pt");

  font_size("tiny");

  for(unsigned i = 0; i < 36; i++)
  {

    std::ostringstream out;
    out << i;

    label(P(2 * components[i].posx, components[i].posy * 2), out.str());

  }

  end();
}

