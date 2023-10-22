#ifndef UTILS_H
#define UTILS_H

#include "graph.h"
#include "heap.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *dijkstra_algorithm(Graph *g, int s, int t);

double dijkstra_algorithm_cost(Graph *g, int s, int t);

#endif
