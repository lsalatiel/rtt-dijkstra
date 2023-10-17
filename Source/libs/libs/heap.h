#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_init(int capacity);

void heap_destroy(Heap *h);

void heap_insert(Heap *h, int data, double priority);

int heap_pop(Heap *h);

void heap_decrease_key(Heap *h, int id, double value);

double heap_get_priority(Heap *h, int id);

int heap_min(Heap *h);

int heap_empty(Heap *h);

int heap_size(Heap *h);

#endif

