#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>

void draw_circle(int x0, int y0, int radius);
void fill_circle(SDL_Point center, int radius, SDL_Color color);

#endif