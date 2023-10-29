#include <stdio.h>
#include <stdlib.h>
#include "../libs/rtt.h"
#include "../libs/graph.h"
#include "../libs/utils.h"
#include "../libs/heap.h"

double RTT(Graph *g, int a, int b, double *dists_a, double *dists_b) {
    return dists_a[b] + dists_b[a];
}
