#ifndef __STACK_H
#define __STACK_H

#include "../queue/queue.h"

typedef Node *Stack;

void stack__new(Stack *s);
int stack__isEmpty(Stack *s);
int stack__push(Stack *s, void *value);
void * stack__pop(Stack *s);

#endif