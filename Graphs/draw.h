#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>


void fill_circle(int x, int y, int radius, int r, int g, int b, int a);

int load_global_font(const char* path);
void draw_text(int x, int y, const char* text);
int create_edge_text_info();
int update_edge_text_info(int);
int update_all_edge_text_info();

#endif