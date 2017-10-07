#include "draw.h"
#include "loop.h"

void fill_circle(SDL_Point center, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy*dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(gRenderer, center.x + dx, center.y + dy);
			}
		}
	}
}

void draw_circle(int x0, int y0, int radius)
{
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		//putpixel(x0 + x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 + y);
		//putpixel(x0 + y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 + x);
		//putpixel(x0 - y, y0 + x);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 + x);
		//putpixel(x0 - x, y0 + y);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 + y);
		//putpixel(x0 - x, y0 - y);
		SDL_RenderDrawPoint(gRenderer, x0 - x, y0 - y);
		//putpixel(x0 - y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 - y, y0 - x);
		//putpixel(x0 + y, y0 - x);
		SDL_RenderDrawPoint(gRenderer, x0 + y, y0 - x);
		//putpixel(x0 + x, y0 - y);
		SDL_RenderDrawPoint(gRenderer, x0 + x, y0 - y);
		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}