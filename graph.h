#ifndef __GRAPH_H
#define __GRAPH_H

#include "queue/queue.h"
#include "stack/stack.h"
#include "binary-heap/binary-heap.h"

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
    int weight;
    struct _adjListNode *next;
} AdjListNode, *AdjList;

typedef struct _vertice {
    int distance;
    int previous;
    AdjList list;
} Vertice;

typedef struct _graph {
    int numVertices;
    Vertice* vertice;
} Graph;


AdjListNode * __new_adjListNode(int dest, int weight);
Vertice * __new_vertices_array(int numVertices);
int __topologicalSorting(Graph *g, int* entryDegree, Queue* topologicalQueue);

int graph__newGraph(Graph *g, int numVertices);
void graph__freeGraph(Graph *g);
int graph__newEdgeUndirected(Graph *g, int src, int dest, int weight);
int graph__newEdgeDirected(Graph *g, int src, int dest, int weight);

int graph__topologicalSorting(Graph *g, Queue* topologicalQueue);
int graph__calculateMinPaths(Graph *g, int src);
int graph__calculateDijkstra(Graph *g, int src);
int graph__getPath(Graph *g, Stack *s, int src, int dest);

#endif