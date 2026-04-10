#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

int kruskal_mst(const Graph *graph, Edge mst_edges[], int *mst_edge_count, int *total_weight);
int prim_mst(const Graph *graph, Edge mst_edges[], int *mst_edge_count, int *total_weight);
int dijkstra_shortest_path(
    const Graph *graph,
    int start,
    int end,
    int path[],
    int *path_length,
    int *total_distance);

#endif
