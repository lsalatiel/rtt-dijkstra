#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_init(int capacity);

void heap_destroy(Heap *h);

void heap_insert(Heap *h, int data, double priority);

int heap_pop(Heap *h);

int heap_empty(Heap *h);

int heap_size(Heap *h);

#endif
