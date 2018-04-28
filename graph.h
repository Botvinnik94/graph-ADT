#ifndef __GRAPH_H
#define __GRAPH_H

#include "queue/queue.h"
#include "stack/stack.h"

#define INFINITE 2147483647

#define RETURN_ON_FAILURE(value)        \
    do{                                 \
        if((value) == 1){               \
            return 1;                   \
        }                               \
    } while(0)

#define SAVE_ON_HEAP(src, srcptr)       \
    do{                                 \
        srcptr = malloc(sizeof(src));   \
        if(srcptr == NULL) return 1;    \
        *srcptr = src;                  \
    } while(0)

typedef struct _adjListNode {
    int dest;
    struct _adjListNode *next;
} AdjListNode, *AdjList;

typedef struct _vertice {
    AdjList list;
} Vertice;

typedef struct _graph {
    int numVertices;
    Vertice* vertice;
} Graph;


AdjListNode * __new_adjListNode(int dest);
Vertice * __new_vertices_array(int numVertices);
int __topologicalSorting(Graph *g, int* entryDegree, Queue* topologicalQueue);

int graph__newGraph(Graph *g, int numVertices);
int graph__newEdgeUndirected(Graph *g, int src, int dest);
int graph__newEdgeDirected(Graph *g, int src, int dest);

int graph__topologicalSorting(Graph *g, Queue* topologicalQueue);

#endif