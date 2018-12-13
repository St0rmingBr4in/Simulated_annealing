#pragma once

#include "meta.h"
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

void sdlinit();
void init_board();
SDL_Rect camera();
void draw(struct component components[]);
