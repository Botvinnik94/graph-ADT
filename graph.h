#ifndef __GRAPH_H
#define __GRAPH_H

#include "queue/queue.h"
#include "stack/stack.h"

#define INFINITE 2147483647

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
int __topologicalSorting(Graph *g, int* visited, int* entryDegree, Stack* s);

int graph__newGraph(Graph *g, int numVertices);
int graph__newEdgeUndirected(Graph *g, int src, int dest);
int graph__newEdgeDirected(Graph *g, int src, int dest);

Stack graph__topologicalSorting(Graph *g);

#endif