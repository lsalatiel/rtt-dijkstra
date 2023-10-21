#include "../libs/heap.h"
#include <stdlib.h>

struct Heap {
    int *data;
    double *priority;
    int *map;
    size_t size;
    size_t capacity;
};

Heap *heap_init(int capacity) {
    Heap *h = malloc(sizeof(Heap));

    h->data = malloc(sizeof(int) * capacity);
    h->priority = malloc(sizeof(double) * capacity);
    h->map = malloc(sizeof(int) * capacity);

    h->size = 0;
    h->capacity = capacity;

    return h;
}

void heap_destroy(Heap *h) {
    free(h->data);
    free(h->priority);
    free(h->map);
    free(h);
}

void __heap_swap(Heap *h, int i, int j) {
    h->data[i] ^= h->data[j];
    h->data[j] ^= h->data[i];
    h->data[i] ^= h->data[j];

    double aux = h->priority[i];
    h->priority[i] = h->priority[j];
    h->priority[j] = aux;

    h->map[h->data[i]] = i;
    h->map[h->data[j]] = j;
}

void __heapify_up(Heap *h, int i) {
    int parent = (i - 1) / 2;

    if(h->priority[parent] > h->priority[i]) {
        __heap_swap(h, i, parent);
        return __heapify_up(h, parent);
    }
}

void __heapify_down(Heap *h, int i) {
    int left = (i >> 2) + 1;
    int right = (i >> 2) + 2;
    int min = i;

    if(left >= 0 && left < h->size && h->priority[left] < h->priority[i])
        min = left;
    if(right >= 0 && right < h->size && h->priority[right] < h->priority[min])
        min = right;

    if(min != i) {
        __heap_swap(h, i, min);
        __heapify_down(h, min);
    }
}

void heap_insert(Heap *h, int data, double priority) {
    h->data[h->size] = data;
    h->map[data] = h->size;
    h->priority[h->size++] = priority;

    __heapify_up(h, h->size - 1);
}

int heap_pop(Heap *h) {
    int to_remove = h->data[0];

    h->data[0] = h->data[--(h->size)];
    h->priority[0] = h->priority[h->size];

    __heapify_down(h, 0);

    return to_remove;
}

void heap_decrease_key(Heap *h, int id, double value) {
    int i = h->map[id];
    h->priority[i] = value;
    __heapify_up(h, i);
}

double heap_get_priority(Heap *h, int id) {
    return h->priority[h->map[id]];
}

int heap_min(Heap *h) { return h->data[0]; }

int heap_empty(Heap *h) { return h->size == 0; }

int heap_size(Heap *h) { return h->size; }

