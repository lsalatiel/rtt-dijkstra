#include <stdio.h>
#include <stdlib.h>
#include "../libs/priority_queue.h"

static Item *priority_queue;
static int *map;
static int N;

static void swap(int i, int j) {
    exch(priority_queue[i], priority_queue[j]);
    map[id(priority_queue[i])] = i;
    map[id(priority_queue[j])] = j;
}

void fix_up(Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j);
    k = j;
  }
}

void priority_queue_init(int maxN) {
    priority_queue = (Item *) malloc((maxN+1) * sizeof (Item));
    map = (int *) malloc((maxN+1) * sizeof (int));
    N = 0;
}

void priority_queue_insert(Item v) {
    N++;
    priority_queue[N] = v;
    map[id(v)] = N;
    fix_up(priority_queue, N);
}

Item priority_queue_delmin() {
    Item min = priority_queue[1];
    swap(1, N);
    N--;
    fix_down(priority_queue, N, 1);
    return min;
}

Item priority_queue_min() {
    return priority_queue[1];
}

void priority_queue_decrease_key(int id, double value) {
    int i = map[id];
    value(priority_queue[i]) = value;
    fix_up(priority_queue, i);
}

bool priority_queue_empty() {
    return N == 0;
}

int  priority_queue_size() {
    return N;
}

void priority_queue_finish() {
    free(priority_queue);
    free(map);
}


