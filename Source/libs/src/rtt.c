#include <stdio.h>
#include <stdlib.h>
#include "../libs/rtt.h"
#include "../libs/graph.h"
#include "../libs/utils.h"
#include "../libs/heap.h"
#include "../libs/item.h"

double RTT(Graph *g, int a, int b){
    return dijkstra_algorithm_cost(g, a, b) + dijkstra_algorithm_cost(g, b, a);
}