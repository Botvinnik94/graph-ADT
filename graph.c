#include "graph.h"

AdjListNode * __new_adjListNode(int dest){
    AdjListNode *newNode;

    newNode = calloc(1, sizeof(newNode));
    if (newNode == NULL) return NULL;

    newNode->dest = dest;
    return newNode;
}

Vertice * __new_vertices_array(int numVertices){
    Vertice *verticesArray;

    verticesArray = calloc(numVertices, sizeof(verticesArray));
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

int graph__newEdgeDirected(Graph *g, int src, int dest)
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

int graph__newEdgeUndirected(Graph *g, int src, int dest)
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

int graph__topologicalSorting(Graph *g, Queue* topologicalQueue){
    int *visited = calloc(g->numVertices, sizeof(int));
    int *entryDegree = calloc(g->numVertices, sizeof(int));
    int i;
    AdjListNode *iterator;

    if(visited == NULL || entryDegree == NULL)
        return 1;

    queue__new(topologicalQueue);

    for(i = 0; i < g->numVertices; i++){
        iterator = g->vertice[i].list;
        while(iterator != NULL){
            entryDegree[iterator->dest]++;
            iterator = iterator->next;
        }
    }

    if (1 == __topologicalSorting(g, visited, entryDegree, topologicalQueue))
        return 1;
    else
        return 0;
}

int __topologicalSorting(Graph *g, int* visited, int* entryDegree, Queue* topologicalQueue){
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