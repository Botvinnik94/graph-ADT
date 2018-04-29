#include "binary-heap.h"

int bheap__newHeap(BinaryHeap *h, int maxSize){

    if(h == NULL || maxSize <= 0) return 1;

    h->elementArray = calloc(maxSize, sizeof(BinaryHeap));
    h->maxSize = maxSize;
    h->size = 0;
    return 0;
}

void bheap__freeHeap(BinaryHeap *h) {
    if(h == NULL) return;

    free(h->elementArray);
    h->elementArray = NULL;
    h->size = -1;
    h->maxSize = -1;
}

int bheap__isEmpty(BinaryHeap *h) {
    if(h == NULL) return -1;

    if(h->size == 0) return 1;
    else             return 0;
}

int bheap__insert(BinaryHeap *h, int key, void *value) {

    if(h->size == h->maxSize - 1) 
        return 1;

    h->size++;
    h->elementArray[h->size].key = key;
    h->elementArray[h->size].value = value;
    __ascendingFiltering(h, h->size);

    return 0;
}

int bheap__remove(BinaryHeap *h, int* key, void **value) {

    if(bheap__isEmpty(h))
        return 1;
    
    *key = h->elementArray[1].key;
    *value = h->elementArray[1].value;

    h->elementArray[1] = h->elementArray[h->size];
    h->size--;
    __descendingFiltering(h, 1);

    return 0;
}

void __ascendingFiltering(BinaryHeap *h, int i) {
    int parentPos = i/2;

    if((parentPos < 1) || (i > h->size))
        return;

    if(h->elementArray[i].key < h->elementArray[parentPos].key){
        Element temp = h->elementArray[i];
        h->elementArray[i] = h->elementArray[parentPos];
        h->elementArray[parentPos] = temp;

        __ascendingFiltering(h, parentPos);
    }
}

void __descendingFiltering(BinaryHeap *h, int i) {
    int childPos = i*2;

    if(childPos > h->size)
        return;

    else{
        if((childPos < h->size) && (h->elementArray[childPos].key > h->elementArray[childPos+1].key)){
            childPos++;
        }

        if(h->elementArray[i].key > h->elementArray[childPos].key){
            Element temp = h->elementArray[i];
            h->elementArray[i] = h->elementArray[childPos];
            h->elementArray[childPos] = temp;
        }
    }
}