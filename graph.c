#include "graph.h"

AdjListNode * __new_adjListNode(size_t dest){
    AdjListNode *newNode;

    newNode = calloc(1, sizeof(newNode));
    if (newNode == NULL) return NULL;

    newNode->dest = dest;
    return newNode;
}

Vertice * __new_vertices_array(size_t numVertices){
    Vertice *verticesArray;

    verticesArray = calloc(numVertices, sizeof(verticesArray));
    return verticesArray;
}

int graph__newGraph(Graph *g, size_t numVertices){
    if(g == NULL) return 1;

    if(numVertices == 0)    return 1;
    g->numVertices = numVertices;
    
    g->vertice = __new_vertices_array(numVertices);
    if(g->vertice == NULL)  return 1;
    else                    return 0;
}

int graph__newEdgeDirected(Graph *g, size_t src, size_t dest)
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

    iterator = __new_adjListNode(dest);
    if(iterator == NULL) return 1;

    if(previous == NULL)
        g->vertice[src].list = iterator;
    else
        previous->next = iterator;

    return 0;
}

int graph__newEdgeUndirected(Graph *g, size_t src, size_t dest)
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
    iteratorSrc = __new_adjListNode(dest);
    if(iteratorSrc == NULL) return 1;

    AdjListNode *iteratorDest = g->vertice[dest].list;
    AdjListNode *previousDest = NULL;
    while(iteratorDest != NULL){
        previousDest = iteratorDest;
        iteratorDest = iteratorDest->next;
    }
    iteratorDest = __new_adjListNode(src);
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