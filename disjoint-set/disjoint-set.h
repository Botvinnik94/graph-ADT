#ifndef __DISJOINT_SET_H
#define __DISJOINT_SET_H

#include "../queue/queue.h"

typedef struct _disjoint_set {
    int *dset;
    size_t size;
} DSet;


int DSet__new(DSet s);
void DSet__free(DSet *s);
int DSet__find(int value, DSet* s);
int DSet__merge(int src, int dest, DSet* s);

#endif