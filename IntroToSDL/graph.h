#pragma once

struct {
	int num;
} typedef Vertex;

struct {
	int v1;
	int v2;
	int weight;
} typedef Edge;

struct {
	int numberOfVertexes;
	Edge* edges;
} typedef Graph;

Graph createGraph(int numVertex, Edge* edges);

Edge* createEdges(int a, ...);