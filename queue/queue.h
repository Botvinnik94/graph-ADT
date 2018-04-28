#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdlib.h>

typedef struct _node {
    void *value;
    struct _node *next;
} Node;

typedef struct _queue {
    Node *top;
    Node *bottom;
} Queue;

int queue__new(Queue *q);
int queue__isEmpty(Queue *q);
int queue__insert(Queue *q, void *value);
void * queue__remove(Queue *q);

Node * __new_Node(void *value);

#endif