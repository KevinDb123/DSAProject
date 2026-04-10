#include "graph.h"

#include <string.h>

void graph_init(Graph *graph)
{
    int i;

    graph->city_count = 0;
    graph->edge_count = 0;

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
    FILE *index_file;
    FILE *distance_file;
    char index_to_name[MAX_CITIES][MAX_CITY_NAME];
    int file_index;
    char city_name[MAX_CITY_NAME];
    int from_index;
    int to_index;
    int weight;
    int i;

    graph_init(graph);

    for (i = 0; i < MAX_CITIES; ++i)
    {
        index_to_name[i][0] = '\0';
    }

    index_file = fopen(index_filename, "r");
    if (index_file == NULL)
    {
        return 0;
    }

    while (fscanf(index_file, "%d %63s", &file_index, city_name) == 2)
    {
        if (file_index < 0 || file_index >= MAX_CITIES)
        {
            fclose(index_file);
            return 0;
        }

        strncpy(index_to_name[file_index], city_name, MAX_CITY_NAME - 1);
        index_to_name[file_index][MAX_CITY_NAME - 1] = '\0';

        if (graph_add_city(graph, city_name) < 0)
        {
            fclose(index_file);
            return 0;
        }
    }
    fclose(index_file);

    distance_file = fopen(distance_filename, "r");
    if (distance_file == NULL)
    {
        return 0;
    }

    while (fscanf(distance_file, "%d %d %d", &from_index, &to_index, &weight) == 3)
    {
        if (from_index < 0 || from_index >= MAX_CITIES ||
            to_index < 0 || to_index >= MAX_CITIES ||
            index_to_name[from_index][0] == '\0' ||
            index_to_name[to_index][0] == '\0')
        {
            fclose(distance_file);
            return 0;
        }

        if (!graph_add_edge(graph, index_to_name[from_index], index_to_name[to_index], weight))
        {
            fclose(distance_file);
            return 0;
        }
    }
    fclose(distance_file);

    return 1;
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
