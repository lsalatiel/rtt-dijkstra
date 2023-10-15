#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>
#include "item.h"

void priority_queue_init(int maxN); // cria uma min PQ com capacidade maxN
void priority_queue_insert(Item);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item priority_queue_delmin();       // Remove Item com menor campo 'value' da PQ
void priority_queue_decrease_key(int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item priority_queue_min();          // Retorna Item com menor campo 'value' da PQ
bool priority_queue_empty();        // Retorna True se a PQ não tem elementos
int  priority_queue_size();         // Número de elementos na PQ
void priority_queue_finish();       // Libera memória

#endif
