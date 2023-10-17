#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#ifndef WEIGHTED
#define WEIGHTED
#endif

#include <stdbool.h>

typedef struct LinkedList LinkedList;

typedef struct ListIterator ListIterator;

// cria uma lista
LinkedList* linked_list_construct();

// retorna o número de elementos na lista
int linked_list_size(LinkedList* l);

// adiciona um item no início da lista
#ifdef WEIGHTED
void linked_list_push_front(LinkedList* l, int val, double weight);

double linked_list_get_weight(LinkedList *l, int val);
#else
void linked_list_push_front(LinkedList* l, int val);
#endif

// mostra a lista na tela
void linked_list_print(LinkedList* l);

// libera o espaço alocado para a lista
void linked_list_destroy(LinkedList* l);

// remove todas as ocorrências de um valor da lista
void linked_list_remove(LinkedList* l, int val);

ListIterator *list_iterator_construct(LinkedList *l);

void list_iterator_free(ListIterator *it);

int list_iterator_next(ListIterator *it);

bool list_iterator_is_over(ListIterator *it);

#endif

