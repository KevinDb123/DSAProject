#include "graph.h"

#include <string.h>

void graph_init(Graph *graph)
{
    int i;

    graph->city_count = 0;
    graph->edge_count = 0;
    graph->reserved = 0;

    for (i = 0; i < MAX_CITIES; ++i)
    {
        graph->city_names[i][0] = '\0';
    }

    /*
     * TODO:
     * Initialize your graph storage.
     * For a matrix, set diagonal to 0 and others to INF_DISTANCE.
     * For a list, initialize all heads to empty.
     */
}

int graph_find_city(const Graph *graph, const char *city_name)
{
    int i;

    for (i = 0; i < graph->city_count; ++i)
    {
        if (strcmp(graph->city_names[i], city_name) == 0)
        {
            return i;
        }
    }

    return -1;
}

int graph_add_city(Graph *graph, const char *city_name)
{
    int index = graph_find_city(graph, city_name);

    if (index >= 0)
    {
        return index;
    }

    if (graph->city_count >= MAX_CITIES)
    {
        return -1;
    }

    strncpy(graph->city_names[graph->city_count], city_name, MAX_CITY_NAME - 1);
    graph->city_names[graph->city_count][MAX_CITY_NAME - 1] = '\0';

    graph->city_count += 1;
    return graph->city_count - 1;
}

int graph_add_edge(Graph *graph, const char *from, const char *to, int weight)
{
    int from_index;
    int to_index;

    if (graph->edge_count >= MAX_EDGES)
    {
        return 0;
    }

    from_index = graph_add_city(graph, from);
    to_index = graph_add_city(graph, to);

    if (from_index < 0 || to_index < 0)
    {
        return 0;
    }

    graph->edges[graph->edge_count].from = from_index;
    graph->edges[graph->edge_count].to = to_index;
    graph->edges[graph->edge_count].weight = weight;
    graph->edge_count += 1;

    /*
     * TODO:
     * Insert this undirected edge into your graph storage.
     * Remember to update both directions.
     */

    return 1;
}

int graph_load_from_files(
    Graph *graph,
    const char *index_filename,
    const char *distance_filename)
{
    graph_init(graph);

    /*
     * TODO:
     * Load cities from cities.txt and edges from edges.txt.
     * cities.txt stores: index city_name
     * edges.txt stores: from_index to_index weight
     * You may switch to cities_zh.txt if you want Chinese names.
     * Build an index-to-name mapping first, then add edges.
     */

    return 0;
}

void graph_print_cities(const Graph *graph)
{
    int i;

    printf("Cities (%d):\n", graph->city_count);
    for (i = 0; i < graph->city_count; ++i)
    {
        printf("%2d. %s\n", i + 1, graph->city_names[i]);
    }
}
