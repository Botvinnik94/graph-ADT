#include "stack.h"

void stack__new(Stack *s) {
    *s = NULL;
}

int stack__isEmpty(Stack *s) {
    if(*s == NULL)   return 1;
    else             return 0;
}

int stack__push(Stack *s, void *value) {
    Node *newNode;

    newNode = __new_Node(value);
    if(newNode == NULL) return 1;

    newNode->next = *s;
    *s = newNode;

    return 0;
}

void * stack__pop(Stack *s) {
    void *value;
    Node *toRemove;

    if(stack__isEmpty(s)) return NULL;

    value = (*s)->value;
    toRemove = *s;
    *s = (*s)->next;
    free(toRemove);

    return value;
}