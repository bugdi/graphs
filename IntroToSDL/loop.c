#include "loop.h"
#include "draw.h"
#include "graph.h"
#include "vector_math.h"
//#include <SDL.h>
#define VERTEX_RADIUS 6.0

SDL_Renderer* gRenderer = NULL;
Graph* gGraph = NULL;
int selectedVertex = -1;
int selectedEdge = -1;
int action = 0;
Vector2i mouse;
Vector2i mouseFrom;


void gameInit()
{

	Vector2d intersect = intersect_lines(
		0, 0, 
		1, 1, 
		
		2, 0,
		0, 2);

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
Vector2i vertex_to_vector(Vertex v)
{
	Vector2i vect = { v.x, v.y };
	return vect;
}
Vector2i edge_to_vector(int i)
{
	Vector2i vect = { gGraph->vertices[gGraph->edges[i].v2].x - gGraph->vertices[gGraph->edges[i].v1].x, gGraph->vertices[gGraph->edges[i].v2].y - gGraph->vertices[gGraph->edges[i].v1].y };
	return vect;
}
Vector2i vector_from_vertex_and_vector(Vertex a, Vector2i b)
{
	Vector2i vect = { b.x - a.x, b.y - a.y };
	return vect;
}
int is_between(double num, double min, double max)
{
	return (num > min && num < max);
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
			fill_circle(gGraph->vertices[i].x, gGraph->vertices[i].y, VERTEX_RADIUS, 0xFF, 0x00, 0x00, 0xFF);
		}
		else {
			fill_circle(gGraph->vertices[i].x, gGraph->vertices[i].y, VERTEX_RADIUS, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	if (action == 2)
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(gRenderer, gGraph->vertices[selectedVertex].x, gGraph->vertices[selectedVertex].y, mouse.x, mouse.y);
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	}
}
double distance(int x0, int y0, int x1, int y1)
{
	return ((double)x0 - x1) * ((double)x0 - x1) + ((double)y0 - y1) * ((double)y0 - y1);
}
int get_vertex_at(int x, int y)
{
	int i;
	for (i = 0; i < gGraph->numberOfVertices; i++)
	{
		if (distance(gGraph->vertices[i].x, gGraph->vertices[i].y, x, y) <= VERTEX_RADIUS * VERTEX_RADIUS)
		{
			return i;
		}
	}
	return -1;
}

Vector2d intersect_vertex_and_vector(Vertex a, Vertex b, Vector2i c, Vector2i d)
{
	return intersect_lines(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y);
}

void update(SDL_Event e, int ticks)
{
	
	int i;
	int vertex;
	Vector2i v_edge;
	Vertex v1, v2;
	Vector2d intersection;
	double tX1, tY1, tX2, tY2;
	//Vector2d projA, projB;

	//move
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.clicks == 1)
			{
				selectedVertex = get_vertex_at(e.button.x, e.button.y);
				action = (selectedVertex == -1) ? 0 : 1;
			}
			else if(e.button.clicks == 2) {
				append_vertex(gGraph, e.button.x, e.button.y);
			}
			
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			action = 0;
			selectedVertex = -1;
		}
	}
	else if (e.button.button == SDL_BUTTON_RIGHT)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			mouse.x = e.button.x;
			mouse.y = e.button.y;
			mouseFrom.x = e.button.x;
			mouseFrom.y = e.button.y;
			selectedVertex = get_vertex_at(mouse.x, mouse.y);
			
			action = (selectedVertex != -1) ? 2 : 3;
		}
		else if (SDL_MOUSEBUTTONUP) {
			vertex = get_vertex_at(e.button.x, e.button.y);
			if (action == 2 && vertex != -1)
			{
				append_edge(gGraph, selectedVertex, vertex);
			}
			else if(action == 3) {
				//do cut

				mouse.x = e.button.x;
				mouse.y = e.button.y;


				//v_cut = vector_from_points(mouseFrom, mouse);
				
				for (i = 0; i < gGraph->numberOfEdges; i++)
				{
					//v_edge = edge_to_vector(i);
					v1 = gGraph->vertices[gGraph->edges[i].v1];
					v2 = gGraph->vertices[gGraph->edges[i].v2];
				
					
					intersection = intersect_vertex_and_vector(v1, v2, mouseFrom, mouse);
					tX1 = (intersection.x - (double)v1.x) / (double)(v2.x - v1.x);
					tY1 = (intersection.y - (double)v1.y) / (double)(v2.y - v1.y);
					tX2 = (intersection.x - (double)mouseFrom.x) / (double)(mouse.x - mouseFrom.x);
					tY2 = (intersection.y - (double)mouseFrom.y) / (double)(mouse.y - mouseFrom.y);

					if (is_between(tX1, 0, 1) && is_between(tY1, 0, 1) && is_between(tX2, 0, 1) && is_between(tY2, 0, 1))
					{
						delete_edge(gGraph, i);
						//break;
					}
				}
			}
			selectedVertex = -1;
			action = 0;
		}
	}

	if (e.type == SDL_MOUSEMOTION)
	{
		if (action == 1)
		{
			gGraph->vertices[selectedVertex].x = e.motion.x;
			gGraph->vertices[selectedVertex].y = e.motion.y;
		}
		else if (action == 2)
		{
			mouse.x = e.motion.x;
			mouse.y = e.motion.y;
		}
		
		
	}
	
}