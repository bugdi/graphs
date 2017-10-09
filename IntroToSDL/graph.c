#include "graph.h"
#include <stdarg.h>
#include <stdlib.h>
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

	for (i = 0; i < numOfEdges; i++)
	{
		//Will not work in GCC
		Edge e = { va_arg(args, int), va_arg(args, int), 0 };
		graph->edges[i] = e;
	}

	va_end(args);

	return graph;
}

Edge* create_edges(int numOfEdges, ...)
{
	va_list args;
	//Edges 
	int i;
	va_start(args, numOfEdges);

	Edge* edges = malloc(sizeof(Edge) * numOfEdges);

	for (int i = 0; i < numOfEdges; i++)
	{
		//Will not work in GCC
		Edge e = { va_arg(args, int), va_arg(args, int), 0 };
		edges[i] = e;
	}

	va_end(args);
	return edges;
}

void destroy_graph(Graph* graph)
{
	free(graph->edges);
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
	Edge* new_edges = malloc(sizeof(Edge) * (graph->numberOfEdges + 1));

	//*new_edges = *graph->edges;
	
	for (i = 0; i < graph->numberOfEdges; i++)
	{
		new_edges[i] = graph->edges[i];
	}

	new_edges[graph->numberOfEdges].v1 = v1;
	new_edges[graph->numberOfEdges].v2 = v2;

	graph->numberOfEdges++;

	free(graph->edges);
	graph->edges = new_edges;
}
void delete_edge(Graph* graph, int edge)
{
	int i, n = 0;
	Edge* new_edges = malloc(sizeof(Edge) * (graph->numberOfEdges - 1));

	for (i = 0; i < graph->numberOfEdges; i++)
	{
		if (i != edge)
		{
			new_edges[n++] = graph->edges[i];
		}
	}

	graph->numberOfEdges--;

	free(graph->edges);
	graph->edges = new_edges;
}