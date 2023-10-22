#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Source/libs/libs/graph.h"
#include "../../Source/libs/libs/utils.h"

int main(int argc, char** argv){
    int n_vertices, n_edges;
    int n_servers, n_clients, n_monitors;
    FILE* in = fopen("Input/N10_S3_C3_M3.txt", "r");

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
        fscanf(in, "%d %d %lf", &v1, &v2, &weight);
        graph_add_directed_edge(g, v1, v2, weight);
    }

    fclose(in);

    // RTT
    double cost_dijkstra_s_c = -1;
    double cost_dijkstra_c_s = -1;
    double cost_dijkstra_s_m = -1;
    double cost_dijkstra_m_c = -1;

    for(int i = 0; i < n_servers; i++){
        printf("COST FROM SERVERS TO CLIENTS AND FROM CLIENTS TO SERVERS\n");
        for(int j = 0; j < n_clients; j++){
            printf("(%d, %d): ", servers[i], clients[j]);
            cost_dijkstra_s_c = dijkstra_algorithm_cost(g, servers[i], clients[j]);
            cost_dijkstra_c_s = dijkstra_algorithm_cost(g, clients[j], servers[i]);
            printf("Server %d to Client %d [RTT(%d, %d)]: %lf || ", servers[i], clients[j], servers[i], clients[j], cost_dijkstra_s_c);
            printf("Client %d to Server %d [RTT*(%d, %d)]: %lf\n", clients[j], servers[i], clients[j], servers[i], cost_dijkstra_c_s);
        }

        printf("COST FROM SERVERS TO MONITORS\n");
        for(int j = 0; j < n_monitors; j++){
            printf("(%d, %d): ", servers[i], monitors[j]);
            cost_dijkstra_s_m = dijkstra_algorithm_cost(g, servers[i], monitors[j]);
            printf("Server %d to Monitor %d [RTT(%d, %d)]: %lf\n", servers[i], monitors[j], servers[i], monitors[j], cost_dijkstra_s_m);
        }
        
        printf("COST FROM MONITORS TO CLIENTS\n");
        for(int j = 0; j < n_clients; j++){
            printf("(%d, %d): ", monitors[j], clients[j]);
            cost_dijkstra_m_c = dijkstra_algorithm_cost(g, monitors[j], clients[j]);
            printf("Monitor %d to Client %d [RTT(%d, %d)]: %lf\n", monitors[j], clients[j], monitors[j], clients[j], cost_dijkstra_m_c);
        }

        printf("===========================================================================================================\n\n");
    }

    return 0;
}