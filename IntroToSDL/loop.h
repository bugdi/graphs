#pragma once
#ifndef LOOP_H
#define LOOP_H
#include <SDL.h>
//#include <SDL_render.h>

extern SDL_Renderer* gRenderer;
void draw();
void update(SDL_Event e, int ticks);


#endif
