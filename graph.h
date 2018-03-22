//
//  graph.h
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#ifndef graph_h
#define graph_h

struct staticNode
{
    int key;
    int parent;
    int index; //corresponds to vertex number to keep track with Heap
};

struct adjacencyNode
{
    int nodeNumber;
    int weight;
    struct adjacencyNode *next;
};

struct adjacencyList
{
    struct adjacencyNode *begin;
};

struct Graph
{
    int V;
    int E;
    struct adjacencyList *array;
};

//enum color {white = 1, gray, black};

Graph *newGraph(int V, int E);
adjacencyNode *newAdjacencyNode(int nodeNumber, int weight);
void addEdge(int from, int to, int weight, Graph *graph);
void dijkstra(Graph *graph, int s, int t, bool heapPrint);
void updateArray(Graph *graph, staticNode *nodes, Heap *heap);
Heap *initSingleSource(Graph *graph, int source, int *distanceArray, int *parentArray);
void relax(Heap *heap, int *distanceArray, int *parentArray, int u, int v, int w);
void printParents(int *parentArray, int source, int destination);
void printGraph(Graph *myGraph);

#endif /* graph_h */
