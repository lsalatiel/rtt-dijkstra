#include "../libs/graph.h"
#include "../libs/linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct Graph {
    int num_vertices;
    LinkedList **adjacency_list;
};

Graph *graph_construct(int num_vertices) {
    Graph *g = malloc(sizeof(Graph));

    g->num_vertices = num_vertices;

    g->adjacency_list = malloc(num_vertices * sizeof(LinkedList *));

    for(int i = 0; i < num_vertices; i++) {
        g->adjacency_list[i] = linked_list_construct();
    }

    return g;
}

void graph_destroy(Graph *g) {
    for(int i = 0; i < g->num_vertices; i++) {
        linked_list_destroy(g->adjacency_list[i]);
    }

    free(g->adjacency_list);
    free(g);
}

#ifdef WEIGHTED
void graph_add_undirected_edge(Graph *g, int p, int q, double weight) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_push_front(g->adjacency_list[p], q, weight);
    linked_list_push_front(g->adjacency_list[q], p, weight);
}

void graph_add_directed_edge(Graph *g, int p, int q, double weight) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_push_front(g->adjacency_list[p], q, weight);
}

double graph_get_weight(Graph *g, int p, int q) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return 0.0;

    return linked_list_get_weight(g->adjacency_list[p], q);
}

#else
void graph_add_undirected_edge(Graph *g, int p, int q) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_push_front(g->adjacency_list[p], q);
    linked_list_push_front(g->adjacency_list[q], p);
}

void graph_add_directed_edge(Graph *g, int p, int q) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_push_front(g->adjacency_list[p], q);
}
#endif

void graph_remove_undirected_edge(Graph *g, int p, int q) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_remove(g->adjacency_list[p], q);
    linked_list_remove(g->adjacency_list[q], p);
}

void remove_directed_edge(Graph *g, int p, int q) {
    if(p < 0 || p >= g->num_vertices || q < 0 || q >= g->num_vertices)
        return;

    linked_list_remove(g->adjacency_list[p], q);
}

int graph_num_vertices(Graph *g) {
    return g->num_vertices;
}

LinkedList **graph_adjacency_list(Graph *g) {
    return g->adjacency_list;
}

void graph_print(Graph *g) {
    for(int i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        linked_list_print(g->adjacency_list[i]);
        printf("\n");
    }
}
