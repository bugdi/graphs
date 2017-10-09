#pragma once
#ifndef LOOP_H
#define LOOP_H
#include <SDL.h>
#include "graph.h"
//#include <SDL_render.h>

extern SDL_Window* gWindow;
extern Graph* gGraph;
extern SDL_Renderer* gRenderer;
void draw();
void gameInit();
void gameClose();
void update(SDL_Event e, int ticks);


#endif
