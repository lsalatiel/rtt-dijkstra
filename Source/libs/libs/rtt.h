#ifndef RTT_H
#define RTT_H

#include <stdio.h>
#include <stdlib.h>
#include "../libs/graph.h"
#include "../libs/utils.h"
#include "../libs/heap.h"
#include "../libs/item.h"

/**
 * @brief 
 * 
 * @param g 
 * @param a 
 * @param b 
 * @return double 
 */
double RTT(Graph *g, int a, int b);

#endif