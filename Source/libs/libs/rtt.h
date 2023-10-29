#ifndef RTT_H
#define RTT_H

#include <stdio.h>
#include <stdlib.h>
#include "../libs/graph.h"
#include "../libs/heap.h"

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param dists_a
 * @param dists_b
 * @return double 
 */
double RTT(int a, int b, double *dists_a, double *dists_b);

#endif
