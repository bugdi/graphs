#include "graph.h"
#include <stdarg.h>
#include <stdlib.h>

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
