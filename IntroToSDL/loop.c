#include "loop.h"
#include "draw.h"
//#include <SDL.h>

int playerX = 0, playerY = 0;
int playerVY = 0;
SDL_Renderer* gRenderer = NULL;
void draw_rect(int x, int y, int w, int h)
{
	SDL_Point center = { 40, 40 };
	SDL_Color color = { 0xFF, 0x00, 0x00, 0xFF };
	fill_circle(center, 20, color);
	//draw_rect(playerX, playerY, 30, 60);
}
void update(SDL_Event e, int ticks)
{
	
}