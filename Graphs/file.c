#define _CRT_SECURE_NO_WARNINGS
#include "file.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_HEADER "GPH10"
#define FILE_HEADER_LENGTH 6

int save_graph(Graph* graph, const char* path)
{
	//byte order!!!!

	FILE * file = fopen(path, "wb");
	if (file == NULL)
		return 0;
	fwrite(FILE_HEADER, sizeof(char), FILE_HEADER_LENGTH, file);
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
	char header_buffer[FILE_HEADER_LENGTH];

	if (file == NULL)
		return NULL;

	graph = (Graph*)malloc(sizeof(Graph));

	fread(header_buffer, sizeof(char), FILE_HEADER_LENGTH, file);

	if (strcmp(header_buffer, FILE_HEADER) != 0)
		return NULL;

	fread(&graph->flags, sizeof(((Graph*)0)->flags), 1, file);
	fread(&graph->numberOfVertices, sizeof(((Graph*)0)->vertices), 1, file);
	fread(&graph->numberOfEdges, sizeof(((Graph*)0)->edges), 1, file);

	graph->vertices = (Vertex*)malloc(sizeof(Vertex) * graph->numberOfVertices);
	graph->edges = (Edge*)malloc(sizeof(Edge) * graph->numberOfEdges);

	fread(graph->vertices, sizeof(Vertex), graph->numberOfVertices, file);
	fread(graph->edges, sizeof(Edge), graph->numberOfEdges, file);

	fclose(file);

	graph->edgeInfo = (EdgeTextInfo*)malloc(sizeof(EdgeTextInfo) * graph->numberOfEdges);
	memset(graph->edgeInfo, 0, sizeof(EdgeTextInfo) * graph->numberOfEdges);

	

	return graph;
}