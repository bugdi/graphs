#include "draw.h"
#include "loop.h"
#include "SDL_ttf.h"
#include "graph.h"

TTF_Font* gFont;

#define FONT_SIZE 18


int load_global_font(const char* path)
{
	if (TTF_Init() == -1)
		return 0;

	gFont = TTF_OpenFont(path, FONT_SIZE);
	if (gFont == NULL)
		return 0;
}
int create_edge_text_info()
{
	int i;
	EdgeTextInfo* new_edge_info = malloc(sizeof(EdgeTextInfo) * (gGraph->numberOfEdges));

	for (i = 0; i < gGraph->numberOfEdges - 1; i++)
	{
		new_edge_info[i] = gGraph->edgeInfo[i];
	}

	if(gGraph->edgeInfo != NULL)
		free(gGraph->edgeInfo);
	gGraph->edgeInfo = new_edge_info;

	gGraph->edgeInfo[gGraph->numberOfEdges - 1].texture = NULL;

	update_edge_text_info(gGraph->numberOfEdges - 1);

	return 1;
}
int update_all_edge_text_info()
{
	int i;

	for (i = 0; i < gGraph->numberOfEdges; i++)
	{
		if (!update_edge_text_info(i))
			return 0;
	}
	return 1;
}
int update_edge_text_info(int i)
{
	SDL_Color textColor = { 0, 0, 0 };
	char buffer[5];

	memset(buffer, 0, 5);

	sprintf_s(buffer, 5, "%d", gGraph->edges[i].weight);

	gGraph->edgeInfo[i].length = strlen(buffer);

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, buffer, textColor);

	if (textSurface == NULL)
		return 0;

	if (gGraph->edgeInfo[i].texture != NULL)
		SDL_DestroyTexture(gGraph->edgeInfo[i].texture);

	gGraph->edgeInfo[i].texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	if (gGraph->edgeInfo[i].texture == NULL)
		return 0;

	gGraph->edgeInfo[i].rect.w = textSurface->w;
	gGraph->edgeInfo[i].rect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	return 1;
}
int create_text_texture(const char* text, SDL_Texture **texture, SDL_Rect* rect)
{
	
}

void draw_text(int x, int y, const char* text)
{
	int width, height;
	SDL_Texture *texture;
	SDL_Color textColor = { 0, 0, 0 };
	SDL_Rect rect = { x, y, 0, 0 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, textColor);

	if (textSurface == NULL)
		return 0;


	texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

	if (texture == NULL)
		return 0;
	rect.w = textSurface->w;
	rect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(gRenderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);

}


void fill_circle(int x, int y, int radius, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy*dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(gRenderer, x + dx, y + dy);
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