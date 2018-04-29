#include "graph.h"

AdjListNode * __new_adjListNode(int dest, int weight){
    AdjListNode *newNode;

    newNode = calloc(1, sizeof(newNode));
    if (newNode == NULL) return NULL;

    newNode->dest = dest;
    newNode->weight = weight;
    return newNode;
}

Vertice * __new_vertices_array(int numVertices){
    Vertice *verticesArray;

    verticesArray = calloc(numVertices, sizeof(Vertice));
    return verticesArray;
}

int graph__newGraph(Graph *g, int numVertices){
    if(g == NULL) return 1;

    if(numVertices == 0)    return 1;
    g->numVertices = numVertices;
    
    g->vertice = __new_vertices_array(numVertices);
    if(g->vertice == NULL)  return 1;
    else                    return 0;
}

void graph__freeGraph(Graph *g){
    if (g == NULL) return;

    AdjListNode *iterator, *toRemove;
    int i;
    for(i = 0; i < g->numVertices; i++){
        iterator = g->vertice[i].list;
        while(iterator != NULL){
            toRemove = iterator;
            iterator = iterator->next;
            free(toRemove);
        }
    }
    free(g->vertice);
    g->vertice = NULL;
    g->numVertices = 0;
}

int graph__newEdgeDirected(Graph *g, int src, int dest, int weight)
{
    if(g == NULL) return 1;

    if(src >= g->numVertices || dest >= g->numVertices)
        return 1;

    AdjListNode *iterator = g->vertice[src].list;
    AdjListNode *previous = NULL;
    while(iterator != NULL){
        previous = iterator;
        iterator = iterator->next;
    }

    iterator = __new_adjListNode(dest, weight);
    if(iterator == NULL) return 1;

    if(previous == NULL)
        g->vertice[src].list = iterator;
    else
        previous->next = iterator;

    return 0;
}

int graph__newEdgeUndirected(Graph *g, int src, int dest, int weight)
{
    if(g == NULL) return 1;

    if(src >= g->numVertices || dest >= g->numVertices)
        return 1;

    AdjListNode *iteratorSrc = g->vertice[src].list;
    AdjListNode *previousSrc = NULL;
    while(iteratorSrc != NULL){
        previousSrc = iteratorSrc;
        iteratorSrc = iteratorSrc->next;
    }
    iteratorSrc = __new_adjListNode(dest, weight);
    if(iteratorSrc == NULL) return 1;

    AdjListNode *iteratorDest = g->vertice[dest].list;
    AdjListNode *previousDest = NULL;
    while(iteratorDest != NULL){
        previousDest = iteratorDest;
        iteratorDest = iteratorDest->next;
    }
    iteratorDest = __new_adjListNode(src, weight);
    if(iteratorDest == NULL) {
        free(iteratorSrc);
        return 1;
    }

    if(previousSrc == NULL)
        g->vertice[src].list = iteratorSrc;
    else
        previousSrc->next = iteratorSrc;

    if(previousDest == NULL)
        g->vertice[dest].list = iteratorDest;
    else
        previousDest->next = iteratorDest;

    return 0;
}

int graph__topologicalSorting(Graph *g, Queue* topologicalQueue){
    int *entryDegree = calloc(g->numVertices, sizeof(int));
    int i, returnVal;
    AdjListNode *iterator;

    if(entryDegree == NULL)
        return 1;

    queue__new(topologicalQueue);

    for(i = 0; i < g->numVertices; i++){
        iterator = g->vertice[i].list;
        while(iterator != NULL){
            entryDegree[iterator->dest]++;
            iterator = iterator->next;
        }
    }

    returnVal = __topologicalSorting(g, entryDegree, topologicalQueue);
    free(entryDegree);
    return returnVal;
}

int __topologicalSorting(Graph *g, int* entryDegree, Queue* topologicalQueue){
    Queue q;
    AdjListNode* iterator;
    int i, *v;
    int *index;

    queue__new(&q);

    for(i = 0; i < g->numVertices; i++){
        if(entryDegree[i] == 0){
            SAVE_ON_HEAP(i, index);
            RETURN_ON_FAILURE(queue__insert(&q, index));
        }
    }

    while(!queue__isEmpty(&q)){
        v = (int*)queue__remove(&q);
        RETURN_ON_FAILURE(queue__insert(topologicalQueue, v));

        iterator = g->vertice[*v].list;
        while(iterator != NULL){
            entryDegree[iterator->dest]--;
            if(entryDegree[iterator->dest] == 0){
                SAVE_ON_HEAP(iterator->dest, index);
                RETURN_ON_FAILURE(queue__insert(&q, index));
            }
            iterator = iterator->next;
        }
    }   

    return 0;
}

int graph__calculateMinPaths(Graph *g, int src){
    if(g == NULL || g->numVertices <= src) return 1;

    int i, *v, *nVertexPtr;
    AdjListNode *iterator;
    Queue q;
    queue__new(&q);

    for(i = 0; i < g->numVertices; i++){
        g->vertice[i].distance = INFINITE;
        g->vertice[i].previous = -1;
    }
    g->vertice[src].distance = 0;

    SAVE_ON_HEAP(src, nVertexPtr);
    RETURN_ON_FAILURE(queue__insert(&q, nVertexPtr));

    while(!queue__isEmpty(&q)){
        v = (int*)queue__remove(&q);
        iterator = g->vertice[*v].list;
        while(iterator != NULL){
            if(g->vertice[iterator->dest].distance == INFINITE){
                g->vertice[iterator->dest].distance = g->vertice[*v].distance + 1;
                g->vertice[iterator->dest].previous = *v;

                SAVE_ON_HEAP(iterator->dest, nVertexPtr);
                RETURN_ON_FAILURE(queue__insert(&q, nVertexPtr));
            }
            iterator = iterator->next;
        }
        free(v);
    }

    return 0;
}

int graph__minPath(Graph *g, Stack *s, int src, int dest){
    if(g == NULL || src >= g->numVertices || dest >= g->numVertices)
        return 1;

    stack__new(s);

    int iterator, *iteratorPtr;
    iterator = dest;

    SAVE_ON_HEAP(iterator, iteratorPtr);
    RETURN_ON_FAILURE(stack__push(s, iteratorPtr));
    while(iterator != src){
        iterator = g->vertice[iterator].previous;
        if(iterator == -1) return 1;

        SAVE_ON_HEAP(iterator, iteratorPtr);
        RETURN_ON_FAILURE(stack__push(s, iteratorPtr));
    }

    return 0;
}