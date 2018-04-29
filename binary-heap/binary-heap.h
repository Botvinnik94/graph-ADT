#ifndef __BINARY_HEAP_H
#define __BINARY_HEAP_H

#include "../queue/queue.h"

typedef struct _element {
    int key;
    void *value;
} Element;

typedef struct _bin_heap {
    Element *elementArray;
    int size;
    int maxSize;
} BinaryHeap;

int bheap__newHeap(BinaryHeap *h, int maxSize);
void bheap__freeHeap(BinaryHeap *h);
int bheap__isEmpty(BinaryHeap *h);
int bheap__insert(BinaryHeap *h, int key, void *value);
int bheap__remove(BinaryHeap *h, Element *e);

void __ascendingFiltering(BinaryHeap *h, int i);
void __descendingFiltering(BinaryHeap *h, int i);

#endif