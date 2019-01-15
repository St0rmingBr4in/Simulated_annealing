#include "draw.hh"
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>

SDL_Window* get_screen(void)
{
  static SDL_Window *screen = NULL;
  if (!screen)
    screen = SDL_CreateWindow("Simulated annealing",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL);
  return screen;
}

SDL_Renderer* get_renderer(void)
{
  static SDL_Renderer *renderer = NULL;
  if (!renderer)
    renderer = SDL_CreateRenderer(get_screen(), -1,
                                  SDL_RENDERER_PRESENTVSYNC);
  return renderer;
}

SDL_Texture *get_rendertarget()
{
  static SDL_Texture *tex = NULL;
  if (tex == NULL)
  {
    tex = SDL_CreateTexture(get_renderer(), SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
  }
  return tex;
}

