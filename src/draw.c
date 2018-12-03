#include "draw.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

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

void sdlinit()
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    fprintf(stderr, "SDL Init error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_Window* screen = get_screen();
  SDL_Renderer* renderer = get_renderer();

  if (!screen || !renderer)
  {
    fprintf(stderr, "Failed at init of renderer or screen: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

SDL_Rect camera()
{
  static SDL_Rect res = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  return res;
}

void draw(SDL_Rect *camera)
{
  SDL_SetRenderTarget(get_renderer(), get_rendertarget());

  SDL_RenderPresent(get_renderer());
}


