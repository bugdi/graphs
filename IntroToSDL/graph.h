#pragma once

#define GRAPH_WEIGHTED 1
#define GRAPH_DIRECTED 2

struct {
	int x;
	int y;
} typedef Vertex;

struct {
	int v1;
	int v2;
	int weight;
} typedef Edge;


struct {
	int numberOfVertices;
	int numberOfEdges;
	Vertex* vertices;
	Edge* edges;
	int flags;
} typedef Graph;

Graph* create_graph(int numOfVertices, int numOfEdges, int flags, ...);

void destroy_graph(Graph* graph);

void append_vertex(Graph* graph, int x, int y);

void append_edge(Graph* graph, int v1, int v2);

void delete_edge(Graph* graph, int edge);

void delete_vertex(Graph* graph, int vertex);