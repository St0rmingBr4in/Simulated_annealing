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

void draw(struct component components[36])
{
  SDL_Rect blocs[36];
  SDL_Renderer* renderer = get_renderer();
  //Set background to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  //Clear window
  SDL_RenderClear(renderer);
  //Manage font
  TTF_Init();
  TTF_Font* fantasq = TTF_OpenFont("data/FantasqueSansMono-Regular.ttf", 90);
  if(!fantasq)
    printf("pls %s\n", TTF_GetError());
  SDL_Color Black = {0, 0, 0};
  char *str = malloc(10);

  for(unsigned i = 0; i < 36; i++)
  {
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    blocs[i].w = SCREEN_HEIGHT/6 - 10;
    blocs[i].h = SCREEN_HEIGHT/6 - 10;
    blocs[i].x = components[i].posx * (SCREEN_HEIGHT/6);
    blocs[i].y = components[i].posy * (SCREEN_HEIGHT/6);
    SDL_RenderFillRect(renderer, &blocs[i]);
    sprintf( str,"%u", i);
    SDL_Surface* text_surf = TTF_RenderText_Solid(fantasq, str, Black);
    SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, text_surf);
    SDL_FreeSurface(text_surf);
    SDL_Rect msg_rect;
    msg_rect.x = components[i].posx * (SCREEN_HEIGHT/6);
    msg_rect.y = components[i].posy * (SCREEN_HEIGHT/6);
    msg_rect.w = SCREEN_HEIGHT/6 - 10;
    msg_rect.h = SCREEN_HEIGHT/6 - 10;
    SDL_RenderCopy(renderer, msg, NULL, &msg_rect);
    if(i % 2)
      for(unsigned j = 0; j < components[i].links_nb; j++)
      {
        SDL_SetRenderDrawColor(renderer, 0, rand() % 255, rand() % 255, rand() % 255);
        SDL_RenderDrawLine(renderer, blocs[i].x + (blocs[i].w / 2),
                           blocs[i].y + (blocs[i].h /2),
                           (components[i].components[j]->posx * (SCREEN_HEIGHT/6)) + (blocs[i].w / 2),
                           (components[i].components[j]->posy * (SCREEN_HEIGHT/6)) + (blocs[i].h /2));
      }
  }
  SDL_SetRenderTarget(renderer, get_rendertarget());
  SDL_RenderPresent(renderer);
  SDL_Delay(1000);
}
