#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define MAX_CITIES 32
#define MAX_CITY_NAME 64
#define MAX_EDGES 128
#define INF_DISTANCE 1000000000

typedef struct
{
    int from;
    int to;
    int weight;
} Edge;

typedef struct
{
    int city_count;
    int edge_count;
    char city_names[MAX_CITIES][MAX_CITY_NAME];
    Edge edges[MAX_EDGES];

    /*
     * TODO:
     * Add your graph storage here.
     * You may use an adjacency matrix or an adjacency list.
     * Keep in mind that this is an undirected weighted graph.
     */
    int reserved;
} Graph;

void graph_init(Graph *graph);
int graph_find_city(const Graph *graph, const char *city_name);
int graph_add_city(Graph *graph, const char *city_name);
int graph_add_edge(Graph *graph, const char *from, const char *to, int weight);
int graph_load_from_files(
    Graph *graph,
    const char *index_filename,
    const char *distance_filename);
void graph_print_cities(const Graph *graph);

#endif
