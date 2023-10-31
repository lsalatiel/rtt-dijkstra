#include "../libs/utils.h"
#include "../libs/graph.h"
#include "../libs/heap.h"
#include "../libs/graph.h"
#include "../libs/linked_list.h"
#include "../libs/heap.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double RTT(int a, int b, double *dists_a, double *dists_b) {
    return dists_a[b] + dists_b[a];
}

void __dijkstra_relax(Heap *h, double u_w, int v, double w) {
    double new_priority = u_w + w;
    if(heap_get_priority(h, v) > new_priority) {
        heap_decrease_key(h, v, new_priority);
    }
}

double *dijkstra_algorithm(Graph *g, int s) {
    Heap *h = heap_init(graph_num_vertices(g));
    double *dist = malloc(sizeof(double) * graph_num_vertices(g));

    for(int i = 0; i < graph_num_vertices(g); i++) {
        heap_insert(h, i, i == s ? 0.0 : DBL_MAX);
        dist[i] = i == s ? 0 : DBL_MAX;
    }

    LinkedList **l = graph_adjacency_list(g);

    while(!heap_empty(h)) {
        int u = heap_min(h);
        double u_priority = heap_get_priority(h, u);
        heap_pop(h);

        ListIterator *it = list_iterator_construct(l[u]);
        if(it == NULL) continue;
        while(!list_iterator_is_over(it)) {
            int v = list_iterator_next(it);
            double w = graph_get_weight(g, u, v);
            if(dist[v] > u_priority + w) {
                dist[v] = u_priority + w;
            }
            __dijkstra_relax(h, u_priority, v, w);
        }

        list_iterator_free(it);
    }

    heap_destroy(h);

    return dist;
}

