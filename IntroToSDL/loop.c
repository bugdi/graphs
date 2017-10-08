#include "loop.h"
#include "draw.h"
#include "graph.h"
//#include <SDL.h>
#define VERTEX_RADIUS 5
int playerX = 0, playerY = 0;
int playerVY = 0;
SDL_Renderer* gRenderer = NULL;
Graph* gGraph = NULL;
int selectedVertex = -1;
int selectedEdge = -1;

void draw_rect(int x, int y, int w, int h)
{
	SDL_Point center = { 40, 40 };
	SDL_Color color = { 0xFF, 0x00, 0x00, 0xFF };
	fill_circle(center, 20, color);
	//draw_rect(playerX, playerY, 30, 60);
}
void gameInit()
{
	gGraph = create_graph(3, 3, NULL,
		0, 1,
		1, 2,
		2, 0
	);

	gGraph->vertices[0].x = 40;
	gGraph->vertices[0].y = 40;
	gGraph->vertices[1].x = 80;
	gGraph->vertices[1].y = 40;
	gGraph->vertices[2].x = 80;
	gGraph->vertices[2].y = 80;

}
void gameClose()
{
	destroy_graph(gGraph);
}
void draw()
{
	int i;
	Vertex v1, v2;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF); //black

	//draw edges
	for (i = 0; i < gGraph->numberOfEdges; i++)
	{
		v1 = gGraph->vertices[gGraph->edges[i].v1];
		v2 = gGraph->vertices[gGraph->edges[i].v2];
		if (selectedEdge == i)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawLine(gRenderer, v1.x, v1.y, v2.x, v2.y);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
		else {
			SDL_RenderDrawLine(gRenderer, v1.x, v1.y, v2.x, v2.y);
		}
	}


	//draw vertexes
	for (i = 0; i < gGraph->numberOfVertices; i++)
	{
		if (i == selectedVertex)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			draw_circle(gGraph->vertices[i].x, gGraph->vertices[i].y, VERTEX_RADIUS);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		}
		else {
			draw_circle(gGraph->vertices[i].x, gGraph->vertices[i].y, VERTEX_RADIUS);
		}

	}
}
int distance(int x0, int y0, int x1, int y1)
{
	return ((float)x0 - x1) * ((float)x0 - x1) + ((float)y0 - y1) * ((float)y0 - y1);
}
void update(SDL_Event e, int ticks)
{
	//it's ugly, i know
	static int grabbing = 0;
	int i;

	//move
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			for (i = 0; i < gGraph->numberOfVertices; i++)
			{
				if (distance(gGraph->vertices[i].x, gGraph->vertices[i].y, e.button.x, e.button.y) <= (float)VERTEX_RADIUS + 3.0)
				{
					grabbing = 1;
					selectedVertex = i;
					break;
				}
			}
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			grabbing = 0;
			selectedVertex = -1;
		}
	}

	if (grabbing && e.type == SDL_MOUSEMOTION)
	{
		gGraph->vertices[selectedVertex].x = e.motion.x;
		gGraph->vertices[selectedVertex].y = e.motion.y;
	}
	
}