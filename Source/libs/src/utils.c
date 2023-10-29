#include "../libs/utils.h"
#include "../libs/graph.h"
#include "../libs/heap.h"
#include "../libs/graph.h"
#include "../libs/linked_list.h"
#include "../libs/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void __dijkstra_relax(Heap *h, double *dist, double u_w, int v, double w) {
    double new_priority = u_w + w;
    if(heap_get_priority(h, v) > new_priority) {
        heap_decrease_key(h, v, new_priority);
        dist[v] = new_priority;
    }
}

double __get_set_cost__(double cost, char* op){
    static double v = -1;
    if(strcmp(op, "set") == 0){
        v = cost;
    }
    else{
        return v;
    }
}

void __set_cost__(double cost){
    __get_set_cost__(cost, "set");
}

double __get_cost__() {
    return __get_set_cost__(0, "get");
}

double dijkstra_algorithm_cost(Graph *g, int s, int t){
    int* path = dijkstra_algorithm(g, s, t);
    free(path);
    return __get_cost__();
}

int *dijkstra_algorithm(Graph *g, int s, int t) {
    int *path = malloc(sizeof(int) * graph_num_vertices(g));
    for(int i = 0; i < graph_num_vertices(g); i++) path[i] = -1;
    int path_size = 0;

    Heap *h = heap_init(graph_num_vertices(g));
    double *dist = malloc(sizeof(double) * graph_num_vertices(g));

    for(int i = 0; i < graph_num_vertices(g); i++) {
        heap_insert(h, i, i == s ? 0.0 : INFINITY);
        dist[i] = i == s ? 0 : INFINITY;
    }

    LinkedList **l = graph_adjacency_list(g);

    while(!heap_empty(h)) {
        int u = heap_min(h);
        double u_priority = heap_get_priority(h, u);
        heap_pop(h);
        path[path_size++] = u;
        
        if(u == t) break;

        ListIterator *it = list_iterator_construct(l[u]);
        if(it == NULL) continue;
        while(!list_iterator_is_over(it)) {
            int v = list_iterator_next(it);
            double w = graph_get_weight(g, u, v);
            __dijkstra_relax(h, dist, u_priority, v, w);
        }

        list_iterator_free(it);
    }

    heap_destroy(h);

    __set_cost__(dist[t]);

    free(dist);

    return path;
}

