#include "queue.h"

void queue__new(Queue *q){
    q->top = NULL;
    q->bottom = NULL;
}

int queue__isEmpty(Queue *q){
    if(q->top == NULL)  return 1;
    else                return 0;
}

Node * __new_Node(void *value){
    Node *newNode;

    newNode = calloc(1, sizeof(newNode));
    if(newNode == NULL) return NULL;

    newNode->value = value;
    return newNode;
}

int queue__insert(Queue *q, void *value){
    Node *newNode = __new_Node(value);
    if(newNode == NULL) return 1;

    if(q->top == NULL)  q->top = newNode;
    else                q->bottom->next = newNode;

    q->bottom = newNode;
    return 0;
}

void * queue__remove(Queue *q){
    void *value;
    Node *toRemove;

    if(queue__isEmpty(q)) return NULL;

    value = q->top->value;
    toRemove = q->top;
    q->top = q->top->next;
    free(toRemove);

    return value;
}