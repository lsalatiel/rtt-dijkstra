#include <stdio.h>
#include <stdlib.h>
#include "../libs/linked_list.h"

typedef struct Node {
    int value;
#ifdef WEIGHTED
    double weight;
#endif
    struct Node *next;
} Node;


#ifdef WEIGHTED
Node *node_construct(int value, double weight, Node *next) {
    Node *n = malloc(sizeof(Node));
    
    n->value = value;
    n->weight = weight;
    n->next = next;

    return n;
}

#else
Node *node_construct(int value, Node *next) {
    Node *n = malloc(sizeof(Node));
    
    n->value = value;
    n->next = next;

    return n;
}
#endif

void node_destroy(Node *n) {
    free(n);
}

struct LinkedList {
    int size;
    Node *head;
};

struct ListIterator {
    Node *current;
};

LinkedList* linked_list_construct() {
    LinkedList *l = malloc(sizeof(LinkedList));
    l->size = 0;
    l->head = NULL;

    return l;
}

void node_destroy_recursive(Node *n) {
    if(n == NULL) return;

    node_destroy_recursive(n->next);
    free(n);
}

void linked_list_destroy(LinkedList* l) {
    node_destroy_recursive(l->head);
    free(l);
}

int linked_list_size(LinkedList* l) {
    return l->size;
}

#ifdef WEIGHTED
void linked_list_push_front(LinkedList* l, int val, double weight) {
    Node *n = node_construct(val, weight, l->head);
    l->head = n;

    l->size++;
}

double linked_list_get_weight(LinkedList *l, int val) {
    Node *n = l->head;
    
    while(n != NULL) {
        if(n->value == val)
            return n->weight;
        
        n = n->next;
    }

    return 0.0;
}


#else
void linked_list_push_front(LinkedList* l, int val) {
    Node *n = node_construct(val, l->head);
    l->head = n;

    l->size++;
}
#endif

void linked_list_print(LinkedList* l) {
    Node *n = l->head;
    
    printf("[");
    int i = 0;
    while(n != NULL) {
#ifdef WEIGHTED
        printf("%d, %lf", n->value, n->weight);
#else
        printf("%d", n->value);
#endif
        if(i != l->size - 1)
            printf("; ");
        
        n = n->next;

        i++;
    }
    
    printf("]\n");

    l->size++;
}

void linked_list_remove(LinkedList* l, int val) {
    if(l->head == NULL) return;

    Node *prev = NULL;
    Node *curr = l->head;
    
    while(curr) {
        int remove = 0;
        if(curr->value == val) {
            if(!prev)
                l->head = curr->next;
            else
                prev->next = curr->next;
            remove = 1;
            l->size--;
        }
        else
            prev = curr;
        
        Node *to_remove = curr;
        curr = curr->next;

        if(remove)
            free(to_remove);
    }
}

ListIterator *list_iterator_construct(LinkedList *l) {
    if(l == NULL) return NULL;
    ListIterator *it = malloc(sizeof(ListIterator));

    it->current = l->head;

    return it;
}

void list_iterator_free(ListIterator *it) {
    free(it);
}

int list_iterator_next(ListIterator *it) {
    int value = it->current->value;
    it->current = it->current->next;

    return value;
}

bool list_iterator_is_over(ListIterator *it) {
    return (it->current == NULL);
}
