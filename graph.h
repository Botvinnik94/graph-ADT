#ifndef __GRAPH_H
#define __GRAPH_H

#include "queue/queue.h"

#define INFINITE 2147483647

typedef struct _adjListNode {
    size_t dest;
    struct _adjListNode *next;
} AdjListNode, *AdjList;

typedef struct _vertice {
    AdjList list;
} Vertice;

typedef struct _graph {
    size_t numVertices;
    Vertice* vertice;
} Graph;


AdjListNode * __new_adjListNode(size_t dest);
Vertice * __new_vertices_array(size_t numVertices);

int graph__newGraph(Graph *g, size_t numVertices);
int graph__newEdgeUndirected(Graph *g, size_t src, size_t dest);
int graph__newEdgeDirected(Graph *g, size_t src, size_t dest);

#endif