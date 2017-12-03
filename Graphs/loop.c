#include "loop.h"
#include "draw.h"
//#include "graph.h"
#include "vector_math.h"
#include "file.h"
#include <string.h>
#include <stdio.h>
//#include <SDL_ttf.h>
//#include <SDL.h>
#define VERTEX_RADIUS 6.0
#define WEIGHT_NUM_DIGITS 5

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Graph* gGraph = NULL;
int selectedVertex = -1;
int selectedEdge = -1;
int lastAddedEdge = -1;
int selectedVertexAlgorithm1;

#define ACTION_NOTHING 0
#define ACTION_GRAB_VERTEX 1
#define ACTION_DRAW_EDGE 2
#define ACTION_SELECT_EDGE 3
#define ACTION_START_POINT 5

/*
	actions:
		0: nothing
		1: grab vertex
		2: draw line
		3: select edge ('cutting')
		4: set weight (not used)
		5: select startpoint for algorithm
*/
int action = 0;
Vector2i mouse;
Vector2i mouseFrom;


void gameInit()
{
	gGraph = create_graph(0, 0, 0);
	//gGraph = load_graph("output.gph");
}
void gameClose()
{
	//save_graph(gGraph, "output.gph");
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
	double middle_x;
	double middle_y;
	//double delta;
	int length = 3;
	//char digit_buffer[WEIGHT_NUM_DIGITS];
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
		if (gGraph->flags & GRAPH_WEIGHTED )
		{
			middle_x = (v1.x + v2.x) / 2;
			middle_y = (v1.y + v2.y) / 2;


			gGraph->edgeInfo[i].rect.x = middle_x - (gGraph->edgeInfo[i].length - 1) * 18;
			gGraph->edgeInfo[i].rect.y = middle_y - 20;
			SDL_RenderCopy(gRenderer, gGraph->edgeInfo[i].texture, NULL, &gGraph->edgeInfo[i].rect);

			
			//draw_text(middle_x - (length - 1) * 18, middle_y - 20, digit_buffer);
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

	if (action == ACTION_DRAW_EDGE)
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

void update_weight(int input)
{
	if (selectedEdge != -1 && gGraph->edges[selectedEdge].weight < 1000)
	{
		gGraph->edges[selectedEdge].weight *= 10;
		gGraph->edges[selectedEdge].weight += input;
		update_edge_text_info(selectedEdge);
	}
}

void update(SDL_Event e, int ticks)
{
	
	int i;
	int vertex;
	Vertex v1, v2;
	Vector2d intersection;
	double tX1, tY1, tX2, tY2;
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.clicks == 1)
			{
				selectedVertex = get_vertex_at(e.button.x, e.button.y);
				action = (selectedVertex == -1) ? ACTION_NOTHING : ACTION_GRAB_VERTEX;
			}
			else if(e.button.clicks == 2)
			{
				selectedVertex = get_vertex_at(e.button.x, e.button.y);
				if (selectedVertex == -1)
				{
					append_vertex(gGraph, e.button.x, e.button.y);
				}
				else
				{
					delete_vertex(gGraph, selectedVertex);
				}
			}
			
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			action = ACTION_NOTHING;
			selectedVertex = -1;
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			if (action == ACTION_GRAB_VERTEX)
			{
				gGraph->vertices[selectedVertex].x = e.motion.x;
				gGraph->vertices[selectedVertex].y = e.motion.y;
			}
			
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
			
			action = (selectedVertex != -1) ? ACTION_DRAW_EDGE : ACTION_SELECT_EDGE; //draw or select

			
		}
		else if (e.type == SDL_MOUSEBUTTONUP) {
			vertex = get_vertex_at(e.button.x, e.button.y);
			if (action == ACTION_DRAW_EDGE && selectedVertex != -1 && vertex != -1)
			{
				append_edge(gGraph, selectedVertex, vertex);
			}
			else if(action == ACTION_SELECT_EDGE) {
				//do cut

				mouse.x = e.button.x;
				mouse.y = e.button.y;

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
						selectedEdge = i;
						//delete_edge(gGraph, i);
						//i = 0;
						//break;
					}
				}
			}
			selectedVertex = -1;
			action = ACTION_NOTHING;
		}
	}

	if (e.type == SDL_MOUSEMOTION && action == ACTION_DRAW_EDGE)
	{
		mouse.x = e.motion.x;
		mouse.y = e.motion.y;
	}

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.scancode >= SDL_SCANCODE_1 /* 30 */ && e.key.keysym.scancode < SDL_SCANCODE_0 /* 39 */)
		{
			update_weight(e.key.keysym.scancode - 29);
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_0)
		{
			update_weight(0);
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			if (selectedEdge != -1)
			{
				gGraph->edges[selectedEdge].weight /= 10;
			}
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_D && selectedEdge != -1)
		{
			delete_edge(gGraph, selectedEdge);
			selectedEdge = -1;
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_R) {
			action = ACTION_START_POINT;
		}
	}
	
	
}