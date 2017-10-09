#ifndef FILE_H
#define FILE_H
#include "graph.h"

int save_graph(Graph* graph, const char* path);
Graph* load_graph(const char* path);

#endif