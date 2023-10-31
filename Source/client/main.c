#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/libs/graph.h"
#include "../libs/libs/heap.h"
#include "../libs/libs/rtt.h"
#include "../libs/libs/utils.h"

typedef struct rtt_adt{
    int a;
    int b;
    double rtt;
} rtt_adt;

int compare_rtt_adt(const void *a, const void *b){
    rtt_adt *x = (rtt_adt *) a;
    rtt_adt *y = (rtt_adt *) b;

    if(x->rtt < y->rtt){
        return -1;
    }
    else if(x->rtt > y->rtt){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc, char **argv) {
    if(argc != 3){
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int n_vertices, n_edges;
    int n_servers, n_clients, n_monitors;
    FILE* in = fopen(argv[1], "r");

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

#ifdef BENCHMARK
    #include <time.h>
    clock_t setup_time = clock();
#endif

    Graph* g = graph_construct(n_vertices);

    for(int i = 0; i<n_edges; i++){
        int v1, v2;
        double weight;
        fscanf(in, "%d %d %lf", &v1, &v2, &weight);
        graph_add_directed_edge(g, v1, v2, weight);
    }

#ifdef BENCHMARK
    printf("Graph construction: %lf\n", (double)(clock() - setup_time) / CLOCKS_PER_SEC);
#endif

    fclose(in);

    // RTT
    rtt_adt *rtt_adt_array = malloc(sizeof(rtt_adt) * n_servers * n_clients);
    double min = 0;
    double rtt = 0;
    double rtt_star= 0;

#ifdef BENCHMARK
    clock_t servers_time = clock();
#endif

    double **dist_servers = malloc(sizeof(double *) * n_servers);
    for(int i = 0; i < n_servers; i++) {
        dist_servers[i] = dijkstra_algorithm(g, servers[i]);
    }

#ifdef BENCHMARK
    printf("Getting servers distances: %lf\n", (double)(clock() - servers_time) / CLOCKS_PER_SEC);

    clock_t clients_time = clock();
#endif

    double **dist_clients = malloc(sizeof(double *) * n_clients);
    for(int i = 0; i < n_clients; i++) {
        dist_clients[i] = dijkstra_algorithm(g, clients[i]);
    }

#ifdef BENCHMARK
    printf("Getting clients distances: %lf\n", (double)(clock() - clients_time) / CLOCKS_PER_SEC);

    clock_t monitors_time = clock();
#endif

    double **dist_monitors = malloc(sizeof(double *) * n_monitors);
    for(int i = 0; i < n_monitors; i++) {
        dist_monitors[i] = dijkstra_algorithm(g, monitors[i]);
    }

#ifdef BENCHMARK
    printf("Getting monitors distances: %lf\n", (double)(clock() - monitors_time) / CLOCKS_PER_SEC);

    clock_t rtt_time = clock();
#endif

    for(int i = 0; i < n_servers; i++) {
        for(int j = 0; j < n_clients; j++) {
            rtt = RTT(servers[i], clients[j], dist_servers[i], dist_clients[j]);
            for(int k = 0; k < n_monitors; k++) {
                rtt_star = RTT(servers[i], monitors[k], dist_servers[i], dist_monitors[k]) + RTT(monitors[k], clients[j], dist_monitors[k], dist_clients[j]);
                if(rtt_star < min || k == 0){
                    min = rtt_star;
                }
            }
            rtt_star = min;
            rtt_adt_array[i * n_clients + j].a = servers[i];
            rtt_adt_array[i * n_clients + j].b = clients[j];
            rtt_adt_array[i * n_clients + j].rtt = rtt_star/rtt;
        }
    }

#ifdef BENCHMARK
    printf("Calulating RTT: %lf\n", (double)(clock() - rtt_time) / CLOCKS_PER_SEC);
#endif

    for(int i = 0; i < n_servers; i++)
        free(dist_servers[i]);
    free(dist_servers);

    for(int i = 0; i < n_clients; i++)
        free(dist_clients[i]);
    free(dist_clients);

    for(int i = 0; i < n_monitors; i++)
        free(dist_monitors[i]);
    free(dist_monitors);

    free(servers);
    free(clients);
    free(monitors);
    graph_destroy(g);

#ifdef BENCHMARK
    clock_t sort_time = clock();
#endif

    qsort(rtt_adt_array, n_servers * n_clients, sizeof(rtt_adt), compare_rtt_adt);

#ifdef BENCHMARK
    printf("Sorting RTT: %lf\n", (double)(clock() - sort_time) / CLOCKS_PER_SEC);
#endif

    FILE *out = fopen(argv[2], "w");

    for(int i = 0; i < n_servers * n_clients; i++){
        fprintf(out, "%d %d %.16lf\n", rtt_adt_array[i].a, rtt_adt_array[i].b, rtt_adt_array[i].rtt);
    }

    free(rtt_adt_array);

    fclose(out);

    return 0;
}
