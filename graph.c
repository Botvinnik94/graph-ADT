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

int graph__calculateDijkstra(Graph *g, int src){
    if(g == NULL || g->numVertices <= src) return 1;

    int i, cost, *v, *nVertexPtr, *visited;
    AdjListNode *iterator;
    BinaryHeap h;
    Element e;

    visited = calloc(g->numVertices, sizeof(int));
    if(visited == NULL) return 1;

    for(i = 0; i < g->numVertices; i++){
        g->vertice[i].distance = INFINITE;
        g->vertice[i].previous = -1;
    }
    g->vertice[src].distance = 0;

    bheap__newHeap(&h, 100);

    SAVE_ON_HEAP(src, nVertexPtr);
    RETURN_ON_FAILURE(bheap__insert(&h, 0, nVertexPtr));

    while(!bheap__isEmpty(&h)){
        bheap__remove(&h, &e);
        v = (int*)e.value;
        if(visited[*v] == 0){
            visited[*v] = 1;
            iterator = g->vertice[*v].list;

            while(iterator != NULL){
                if(visited[iterator->dest] == 0){
                    cost = g->vertice[*v].distance + iterator->weight;

                    if(cost < g->vertice[iterator->dest].distance){
                        g->vertice[iterator->dest].distance = cost;
                        g->vertice[iterator->dest].previous = *v;

                        SAVE_ON_HEAP(iterator->dest, nVertexPtr);
                        RETURN_ON_FAILURE(bheap__insert(&h, cost, nVertexPtr));
                    }

                }
                iterator = iterator->next;
            }
        }
        free(v);
    }

    free(visited);
    bheap__freeHeap(&h);
    return 0;
}

int graph__calculatePrim(Graph *g, int src) {
    if(g == NULL || src >= g->numVertices) return 1;

    int i, cost, *v, *nVertexPtr, *visited;
    AdjListNode *iterator;
    BinaryHeap h;
    Element e;

    visited = calloc(g->numVertices, sizeof(int));
    if(visited == NULL) return 1;

    for(i = 0; i < g->numVertices; i++){
        g->vertice[i].distance = INFINITE;
        g->vertice[i].previous = -1;
    }
    g->vertice[src].distance = 0;

    bheap__newHeap(&h, 100);

    SAVE_ON_HEAP(src, nVertexPtr);
    bheap__insert(&h, 0, nVertexPtr);
    while(!bheap__isEmpty(&h)){
        bheap__remove(&h, &e);
        v = (int*)e.value;
        if(visited[*v] == 0){
            visited[*v] = 1;
            iterator = g->vertice[*v].list;

            while(iterator != NULL){
                if(visited[iterator->dest] == 0 && g->vertice[iterator->dest].distance > iterator->weight){
                    g->vertice[iterator->dest].distance = iterator->weight;
                    g->vertice[iterator->dest].previous = *v;

                    SAVE_ON_HEAP(iterator->dest, nVertexPtr);
                    bheap__insert(&h, iterator->weight, nVertexPtr);
                }
                iterator = iterator->next;
            }
        }
        free(v);
    }

    free(visited);
    bheap__freeHeap(&h);
    return 0;
}

int graph__getPath(Graph *g, Stack *s, int src, int dest){
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

int graph__getSpanningTree(Graph *src, Graph *dest) {
    if (src == NULL)
        return 1;

    int i;

    graph__freeGraph(dest);
    graph__newGraph(dest, src->numVertices);

    for(i = 0; i < dest->numVertices; i++){
        if(src->vertice[i].previous != -1)
            graph__newEdgeUndirected(dest, i, src->vertice[i].previous,
                                              src->vertice[i].distance);
    }

    return 0;
}

int graph__calculateKruskal(Graph *src, Graph *dest) {

    if(src == NULL) return 1;

    int numEdgesAccepted = 0, i, vsrcTop, vdestTop, vsrc, vdest;
    BinaryHeap h;
    Edge e, *eptr;
    Element edgeTmp;
    DSet* vertices = DSet__new(src->numVertices);
    AdjListNode *iterator;

    graph__freeGraph(dest);
    graph__newGraph(dest, src->numVertices);

    bheap__newHeap(&h, 100);
    for(i = 0; i < src->numVertices; i++){
        iterator = src->vertice[i].list;
        while(iterator != NULL){
            e.src = i;
            e.dest = iterator->dest;

            SAVE_ON_HEAP(e, eptr);
            bheap__insert(&h, iterator->weight, eptr);

            iterator = iterator->next;
        }
    }

    while(numEdgesAccepted < src->numVertices - 1){
        bheap__remove(&h, &edgeTmp);

        vsrc = (*(Edge*)edgeTmp.value).src;
        vdest = (*(Edge*)edgeTmp.value).dest;

        vsrcTop = DSet__find(vsrc, vertices);
        vdestTop = DSet__find(vdest, vertices);
        if(vsrcTop != vdestTop){
            DSet__merge(vsrc, vdest, vertices);
            numEdgesAccepted++;

            graph__newEdgeUndirected(dest, vsrc, vdest, edgeTmp.key);
        }

        free(edgeTmp.value);
    }

    DSet__free(vertices);
    bheap__freeHeap(&h);
    return 0;
}