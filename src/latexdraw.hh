#pragma once
#include "draw.hh"

template <class N>
class latexdrawing : public drawing<N>
{
  public:
  latexdrawing();
  void draw(N) override;
};

#include "latexdraw.hxx"
