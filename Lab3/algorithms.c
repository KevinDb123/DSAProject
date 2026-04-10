#include "algorithms.h"

int kruskal_mst(const Graph *graph, Edge mst_edges[], int *mst_edge_count, int *total_weight)
{
    *mst_edge_count = 0;
    *total_weight = -1;

    /*
     * TODO:
     * Implement MST with Kruskal.
     * Sort edges by weight and avoid cycles.
     * Stop after selecting city_count - 1 edges.
     */

    return 0;
}

int prim_mst(const Graph *graph, Edge mst_edges[], int *mst_edge_count, int *total_weight)
{
    *mst_edge_count = 0;
    *total_weight = -1;

    /*
     * OPTIONAL:
     * Implement MST with Prim if you want an extra method.
     * Expand the tree one vertex at a time using the minimum outgoing edge.
     * Stop after selecting city_count - 1 edges.
     */

    return 0;
}

int dijkstra_shortest_path(
    const Graph *graph,
    int start,
    int end,
    int path[],
    int *path_length,
    int *total_distance)
{
    *path_length = 0;
    *total_distance = -1;

    /*
     * TODO:
     * Implement shortest path with Dijkstra.
     * Track the previous vertex so the final path can be restored.
     * Return 0 if the target is unreachable.
     */

    return 0;
}