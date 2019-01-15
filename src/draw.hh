#pragma once

#include "meta.hh"
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

template <class N>
class drawing
{
  virtual void draw(N components) = 0;
};
