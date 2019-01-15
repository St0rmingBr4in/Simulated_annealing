#pragma once
#include "draw.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* get_screen(void);
SDL_Renderer* get_renderer(void);
SDL_Texture *get_rendertarget();

template <class N>
class SDLdrawing : public drawing<N>
{
  public:
  SDLdrawing();
  void draw(N) override;
};

template <class N>
class latexdrawing : public drawing<N>
{
  void draw(N) override;
};

#include "SDLdraw.hxx"
