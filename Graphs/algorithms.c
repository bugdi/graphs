#include "algorithms.h"
#include "graph.h"
#include <limits.h>

#include <stdio.h>

#define IS_ENDLESS(row, column) dist[(row * columns) + column].is_endless
#define GET_DIST(row, column) dist[(row * columns) + column].distance
#define COPY_DIST_ABOVE(row, column) dist[(row * columns) + column].is_endless = dist[((row - 1) * columns) + column].is_endless; dist[(row * columns) + column].distance = dist[((row - 1) * columns) + column].distance; dist[(row * columns) + column].last_vertex = dist[((row - 1) * columns) + column].last_vertex
#define SET_DIST(row, column, val) dist[(row * columns) + column].is_endless = 0; dist[row * (columns) + column].distance = val
#define SET_DIST_ENDLESS(row, column) dist[(row * columns) + column].is_endless = 1
#define SET_LAST_VERTEX(row, column, val) dist[(row * columns) + column].is_endless = 0; dist[row * (columns) + column].last_vertex = val;
#define GET_LAST_VERTEX(row, column) dist[row * (columns) + column].last_vertex

struct vertex_set {
	int vertex;
	struct vertex_set* next;
} typedef vertex_set_t;

struct dist_item {
	int distance;
	int last_vertex;
	int is_endless;
} typedef dist_item_t;


int in_set(vertex_set_t* set, int vertex)
{
	vertex_set_t* p = set;

	do {

		if (p->vertex == vertex)
			return 1;

		p = p->next;
	} while (p != NULL);

	return 0;
}

int is_adjacent(Graph* graph, int u, int v, int* edge)
{
	int i;

	for (i = 0; i < graph->numberOfEdges; i++)
	{
		if ((graph->edges[i].v1 == u && graph->edges[i].v2 == v) || (graph->edges[i].v1 == v && graph->edges[i].v2 == u))
		{
			if(edge != NULL)
				*edge = i;

			return 1;
		}
	}
	return 0;
}
int select_minimal_dist_not_in_set(dist_item_t* dist, int columns, int row, vertex_set_t* set)
{
	int i;
	int min = INT_MAX;
	int min_v = -1;
	int cd = 0;

	for(i = 0; i < columns; i++)
	{
		cd = GET_DIST(row, i);
		if (!IS_ENDLESS(row, i) && GET_DIST(row, i) < min && !in_set(set, i))
		{
			min = GET_DIST(row, i);
			min_v = i;
		}
	}
	if (min_v == -1)
		return -1;
	else
		return min_v;
}
void append_to_set(vertex_set_t** set, int vertex)
{
	vertex_set_t* new_item = (vertex_set_t*)malloc(sizeof(vertex_set_t));
	new_item->next = *set;
	new_item->vertex = vertex;
	*set = new_item;
}
void print(Graph* graph, dist_item_t* dist)
{
	int i, j;
	int columns = graph->numberOfVertices;
	for (i = 0; i < graph->numberOfVertices - 1; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (IS_ENDLESS(i, j))
				printf("e(-) ");
			else
				printf("%d(%d) ", GET_DIST(i, j), GET_LAST_VERTEX(i,j));
		}
		printf("\n");
	}
	printf("\n");
}
void free_set(vertex_set_t* head)
{
	vertex_set_t* tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}

}
void highlight_edge_between(Graph* graph, int u, int v)
{
	int i;

	for (i = 0; i < graph->numberOfEdges; i++)
	{
		if ((graph->edges[i].v1 == u && graph->edges[i].v2 == v) || (graph->edges[i].v1 == v && graph->edges[i].v2 == u))
		{
			graph->edgeInfo[i].highlight = 1;
			return;
		}
	}
}
void run_dijkstra(Graph* graph, int start, int end)
{
	dist_item_t* dist = (dist_item_t*)malloc(sizeof(dist_item_t) * (graph->numberOfVertices) *  (graph->numberOfVertices));
	int columns = graph->numberOfVertices;
	int i, j;
	int vertex;
	int edge;
	int init_min = INT_MAX;
	int init_min_v = -1;

	vertex_set_t* set = (vertex_set_t*)malloc(sizeof(vertex_set_t));
	
	set->vertex = start;
	set->next = NULL;
	
	//init dist
	
	for (i = 0; i < columns; i++)
	{
		if (i == start)
		{
			SET_DIST(0, i, 0);
			SET_LAST_VERTEX(0, i, start);
			continue;
		}
		if (is_adjacent(graph, start, i, &edge))
		{
			SET_DIST(0, i, graph->edges[edge].weight);
			SET_LAST_VERTEX(0, i, start);
			//dist[i].is_endless = 0;
			//dist[i].distance = graph->edges[edge].weight;
		}
		else {
			SET_DIST_ENDLESS(0, i);
		}
	}
	for (i = 1; i < graph->numberOfVertices - 1; i++)
	{
		//man waehlt v € V\F wofur D(v) minimal ist
		vertex = select_minimal_dist_not_in_set(dist, columns, i - 1, set);
		append_to_set(&set, vertex);

		SET_DIST(i, vertex, GET_DIST((i - 1), vertex));
		SET_LAST_VERTEX(i, vertex, GET_LAST_VERTEX((i - 1), vertex));

		//SET_DIST(3, 3, 69);

		//print(graph, dist);
		
		for (j = 0; j < columns; j++)
		{
			COPY_DIST_ABOVE(i, j);
			if (!in_set(set, j))
			{
				if (is_adjacent(graph, vertex, j, &edge))
				{
					//Relax(xy): wenn D(x) > D(v) + k(vx)
					if (IS_ENDLESS(i, j))
					{
						SET_DIST(i, j, GET_DIST(i, vertex) + graph->edges[edge].weight);
						SET_LAST_VERTEX(i, j, vertex);
					} else if ((GET_DIST(i, j) > (GET_DIST(i, vertex) + graph->edges[edge].weight)))
					{
						SET_DIST(i, j, GET_DIST(i, vertex) + graph->edges[edge].weight);
						SET_LAST_VERTEX(i, j, vertex);
					}
				}

			}
		}

	}
	
	print(graph, dist);

	//int v;
	vertex = end;
	if (!IS_ENDLESS((graph->numberOfVertices - 2), vertex))
	{
		while (vertex != start)
		{
			highlight_edge_between(graph, vertex, GET_LAST_VERTEX((graph->numberOfVertices - 2), vertex));
			vertex = GET_LAST_VERTEX((graph->numberOfVertices - 2), vertex);
		}
	}

	free_set(set);
	free(dist);

}