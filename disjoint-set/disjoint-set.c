#include "disjoint-set.h"

DSet* DSet__new(size_t size){
    DSet *s;
    s = malloc(sizeof(DSet));
    if(s == NULL) return NULL;

    s->dset = malloc(size * sizeof(int));
    if(s->dset == NULL){
        free(s);
        return NULL;
    }

    int i;
    for(i = 0; i < size; i++)
        s->dset[i] = -1;
    s->size = size;
    return s; 
}

void DSet__free(DSet *s){
    if (s == NULL)
        return;

    free(s->dset);
    free(s);
    s = NULL;
}

int DSet__find(int value, DSet* s){

    if(s == NULL || value >= s->size)
        return -1;

    if(s->dset[value] > -1){
        return DSet__find(s->dset[value], s);
    }

    return value;
}

int DSet__merge(int src, int dest, DSet* s){

    if(s == NULL || src >= s->size || dest >= s->size)
        return -1;

    src = DSet__find(src, s);
    dest = DSet__find(dest, s);

    if(src == dest) return 0;

    if(s->dset[src] == s->dset[dest]){
        s->dset[dest] = src;
        s->dset[src]--;
    }
    else if(s->dset[src] < s->dset[dest])
        s->dset[dest] = src;
    else
        s->dset[src] = dest;

    return 0;
}