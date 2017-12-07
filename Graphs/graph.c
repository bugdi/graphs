#include "graph.h"
#include <stdarg.h>
#include <stdlib.h>
#include "draw.h"
#include <string.h>

Graph* create_graph(int numOfVertices, int numOfEdges, int flags, ...)
{
	va_list args;
	int i;
	//create graph

	Graph* graph = malloc(sizeof(Graph));

	graph->numberOfVertices = numOfVertices;
	graph->numberOfEdges = numOfEdges;

	graph->vertices = (Vertex*)malloc(sizeof(Vertex) * numOfVertices);
	graph->edges = (Edge*)malloc(sizeof(Edge) * numOfEdges);

	//Vertexes

	for (i = 0; i < numOfVertices; i++)
	{
		graph->vertices[i].x = 0;
		graph->vertices[i].y = 0;
	}

	//Edges 
	va_start(args, flags);

	graph->edgeInfo = NULL;

	for (i = 0; i < numOfEdges; i++)
	{
		//Will not work in GCC
		Edge e = { va_arg(args, int), va_arg(args, int), 0 };
		graph->edges[i] = e;
		update_edge_text_info(i);
	}

	va_end(args);

	return graph;
}


void destroy_graph(Graph* graph)
{
	free(graph->edges);
	free(graph->edgeInfo);
	free(graph->vertices);
	free(graph);
}

void append_vertex(Graph* graph, int x, int y)
{
	int i; 
	Vertex* new_vertices = malloc(sizeof(Vertex) * (graph->numberOfVertices + 1));

	//*new_vertices = *graph->vertices;
	for (i = 0; i < graph->numberOfVertices; i++)
	{
		new_vertices[i] = graph->vertices[i];
	}

	new_vertices[graph->numberOfVertices].x = x;
	new_vertices[graph->numberOfVertices].y = y;
	graph->numberOfVertices++;

	free(graph->vertices);
	graph->vertices = new_vertices;
}

void append_edge(Graph* graph, int v1, int v2)
{
	int i;
	Edge* new_edges;

	if (v1 == v2)
		return;

	new_edges = malloc(sizeof(Edge) * (graph->numberOfEdges + 1));

	//*new_edges = *graph->edges;
	
	for (i = 0; i < graph->numberOfEdges; i++)
	{
		new_edges[i] = graph->edges[i];
	}

	new_edges[graph->numberOfEdges].v1 = v1;
	new_edges[graph->numberOfEdges].v2 = v2;
	new_edges[graph->numberOfEdges].weight = 0;

	graph->numberOfEdges++;

	free(graph->edges);
	graph->edges = new_edges;

	create_edge_text_info();
	
}
void delete_edge(Graph* graph, int edge)
{
	int i, n = 0;
	Edge* new_edges = malloc(sizeof(Edge) * (graph->numberOfEdges - 1));
	EdgeTextInfo* new_edge_text_info = malloc(sizeof(EdgeTextInfo) * (graph->numberOfEdges - 1));

	for (i = 0; i < graph->numberOfEdges; i++)
	{
		if (i != edge)
		{
			new_edges[n] = graph->edges[i];
			new_edge_text_info[n++] = graph->edgeInfo[i];
		}
		else {
			SDL_DestroyTexture(graph->edgeInfo[i].texture);
		}
	}

	graph->numberOfEdges--;

	free(graph->edges);
	free(graph->edgeInfo);
	graph->edges = new_edges;
	graph->edgeInfo = new_edge_text_info;
}

void delete_edges_of_vertex(Graph* graph, int vertex)
{
	int i;

	for (i = 0; i < graph->numberOfEdges; i++)
	{
		if (graph->edges[i].v1 == vertex || graph->edges[i].v2 == vertex)
		{
			delete_edge(graph, i);
			i = -1;
		}
	}
}

void delete_vertex(Graph* graph, int vertex)
{
	delete_edges_of_vertex(graph, vertex);
	int i, j, n = 0;
	Vertex* new_vertices = malloc(sizeof(Vertex) * (graph->numberOfVertices - 1));

	for (i = 0; i < graph->numberOfVertices; i++)
	{
		if (i != vertex)
		{
			new_vertices[n++] = graph->vertices[i];
		}	
		if (n - 1 != i)
		{
			for (j = 0; j < graph->numberOfEdges; j++)
			{
				if (graph->edges[j].v1 == i ) {
					graph->edges[j].v1 = n - 1;
				}
				else if (graph->edges[j].v2 == i) {
					graph->edges[j].v2 = n - 1;
				}
			}
		}
	}

	graph->numberOfVertices--;

	free(graph->vertices);
	graph->vertices = new_vertices;
}