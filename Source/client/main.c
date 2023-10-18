#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/libs/graph.h"
#include "../libs/libs/heap.h"
#include "../libs/libs/item.h"

int main(int argc, char** argv){
    int n_vertices, n_edges;
    int n_servers, n_clients, n_monitors;
    FILE* in = fopen(argv[0], "r");

    if(in == NULL){
        printf("Error opening file\n");
        return 1;
    }

    fscanf(in, "%d %d", &n_vertices, &n_edges);
    fscanf(in, "%d %d %d", &n_servers, &n_clients, &n_monitors);

    int* servers = (int*) malloc(n_servers * sizeof(int));
    int* clients = (int*) malloc(n_clients * sizeof(int));
    int* monitors = (int*) malloc(n_monitors * sizeof(int));

    for(int i = 0; i < n_servers; i++){
        fscanf(in, "%d", &servers[i]);
    }

    for(int i = 0; i < n_clients; i++){
        fscanf(in, "%d", &clients[i]);
    }

    for(int i = 0; i < n_monitors; i++){
        fscanf(in, "%d", &monitors[i]);
    }

    Graph* g = graph_construct(n_vertices);

    for(int i = 0; i<n_edges; i++){
        int v1, v2;
        double weight;
        fscanf(in, "%d %d %f", &v1, &v2, &weight);
        graph_add_directed_edge(g, v1, v2, weight);
    }

    fclose(in);

    return 0;
}