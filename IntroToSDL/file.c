#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include <stdio.h>
#include <stdlib.h>


int save_graph(Graph* graph, const char* path)
{
	//byte order!!!!

	FILE * file = fopen(path, "wb");
	if (file == NULL)
		return 0;
	fwrite(&graph->flags, sizeof(graph->flags), 1, file);
	fwrite(&graph->numberOfVertices, sizeof(graph->numberOfVertices), 1, file);
	fwrite(&graph->numberOfEdges, sizeof(graph->numberOfEdges), 1, file);

	fwrite(graph->vertices, sizeof(Vertex), graph->numberOfVertices, file);
	fwrite(graph->edges, sizeof(Edge), graph->numberOfEdges, file);

	fclose(file);
	
	return 1; //success
}
Graph* load_graph(const char* path)
{
	Graph* graph = NULL;
	FILE * file = fopen(path, "rb");
	if (file == NULL)
		return NULL;

	graph = (Graph*)malloc(sizeof(Graph));

	fread(&graph->flags, sizeof(((Graph*)0)->flags), 1, file);
	fread(&graph->numberOfVertices, sizeof(((Graph*)0)->vertices), 1, file);
	fread(&graph->numberOfEdges, sizeof(((Graph*)0)->edges), 1, file);

	graph->vertices = (Vertex*)malloc(sizeof(Vertex) * graph->numberOfVertices);
	graph->edges = (Edge*)malloc(sizeof(Edge) * graph->numberOfEdges);

	fread(graph->vertices, sizeof(Vertex), graph->numberOfVertices, file);
	fread(graph->edges, sizeof(Edge), graph->numberOfEdges, file);

	fclose(file);

	return graph;
}