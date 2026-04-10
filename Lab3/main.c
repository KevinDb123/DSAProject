#include "algorithms.h"
#include "graph.h"

#include <stdio.h>

static void print_menu(void)
{
    printf("\n========== Highway Planner ==========\n");
    printf("1. Show cities\n");
    printf("2. Find shortest path\n");
    printf("3. Build MST with Kruskal\n");
    printf("4. Build MST with Prim (optional)\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
}

static void print_mst_result(const Graph *graph, const Edge mst_edges[], int mst_edge_count, int total_weight)
{
    int i;

    printf("\nMST edges:\n");
    for (i = 0; i < mst_edge_count; ++i)
    {
        printf(
            "%s - %s : %d km\n",
            graph->city_names[mst_edges[i].from],
            graph->city_names[mst_edges[i].to],
            mst_edges[i].weight);
    }
    printf("Total weight: %d km\n", total_weight);
}

static void print_kruskal_mst(const Graph *graph)
{
    Edge mst_edges[MAX_CITIES];
    int mst_edge_count;
    int total_weight;

    if (!kruskal_mst(graph, mst_edges, &mst_edge_count, &total_weight))
    {
        if (total_weight < 0)
        {
            printf("MST is not implemented yet.\n");
        }
        else
        {
            printf("The graph is disconnected.\n");
        }
        return;
    }

    print_mst_result(graph, mst_edges, mst_edge_count, total_weight);
}

static void print_prim_mst(const Graph *graph)
{
    Edge mst_edges[MAX_CITIES];
    int mst_edge_count;
    int total_weight;

    if (!prim_mst(graph, mst_edges, &mst_edge_count, &total_weight))
    {
        if (total_weight < 0)
        {
            printf("Prim is not implemented yet.\n");
        }
        else
        {
            printf("The graph is disconnected.\n");
        }
        return;
    }

    print_mst_result(graph, mst_edges, mst_edge_count, total_weight);
}

static void print_shortest_path(const Graph *graph)
{
    char start_name[MAX_CITY_NAME];
    char end_name[MAX_CITY_NAME];
    int start;
    int end;
    int path[MAX_CITIES];
    int path_length;
    int total_distance;
    int i;

    printf("Enter start city: ");
    if (scanf("%63s", start_name) != 1)
    {
        printf("Input error.\n");
        return;
    }

    printf("Enter end city: ");
    if (scanf("%63s", end_name) != 1)
    {
        printf("Input error.\n");
        return;
    }

    start = graph_find_city(graph, start_name);
    end = graph_find_city(graph, end_name);

    if (start < 0 || end < 0)
    {
        printf("City not found.\n");
        return;
    }

    if (!dijkstra_shortest_path(graph, start, end, path, &path_length, &total_distance))
    {
        if (total_distance < 0)
        {
            printf("Shortest path is not implemented yet.\n");
        }
        else
        {
            printf("No path found.\n");
        }
        return;
    }

    printf("Shortest path: ");
    for (i = 0; i < path_length; ++i)
    {
        printf("%s", graph->city_names[path[i]]);
        if (i != path_length - 1)
        {
            printf(" -> ");
        }
    }
    printf("\nTotal distance: %d km\n", total_distance);
}

int main(void)
{
    Graph graph;
    int choice;

    /* Change cities.txt to cities_zh.txt if you want Chinese city names. */
    if (!graph_load_from_files(&graph, "cities.txt", "edges.txt"))
    {
        printf("Graph loading is not implemented yet.\n");
        return 1;
    }

    printf("Graph loaded: %d cities, %d edges.\n", graph.city_count, graph.edge_count);

    while (1)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Program terminated.\n");
            break;
        }

        if (choice == 0)
        {
            printf("Program exited.\n");
            break;
        }

        switch (choice)
        {
        case 1:
            graph_print_cities(&graph);
            break;
        case 2:
            print_shortest_path(&graph);
            break;
        case 3:
            print_kruskal_mst(&graph);
            break;
        case 4:
            print_prim_mst(&graph);
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }

    return 0;
}
