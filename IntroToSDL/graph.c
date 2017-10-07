#include "graph.h"
#include <stdarg.h>

Graph createGraph(int numVertex, Edge* edges)
{
	
}

Edge* createEdges(int numOfEdges, ...)
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