//
//  graph.cpp
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <limits.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "main.h"
#include "heap.h"
#include "graph.h"
#include "util.h"

using namespace std;

//creates a new graph
Graph *newGraph(int V, int E)
{
    Graph *graph = (Graph*) malloc(sizeof(Graph));
    graph -> V = V;
    graph -> E = E;
    graph -> array = (adjacencyList*) malloc((V + 1) * sizeof(adjacencyList));
    for (int i = 1; i <= V; i++)
        graph -> array[i].begin = NULL;
    return graph;
}

//used to add a new node to the adjacency list
adjacencyNode *newAdjacencyNode(int nodeNumber, int weight)
{
    adjacencyNode *newNode = (adjacencyNode*) malloc(sizeof(adjacencyNode));
    newNode -> nodeNumber = nodeNumber;
    newNode -> weight = weight;
    newNode -> next = NULL;
    return newNode;
}

//used to add new edge
void addEdge(int from, int to, int weight, Graph *graph)
{
    adjacencyNode *newNode = newAdjacencyNode(to, weight);
    newNode -> next = graph -> array[from].begin;
    graph -> array[from].begin = newNode;
}

//perfomrs dijkstra's algorithm to calculate shortest path
void dijkstra(Graph *graph, int s, int t, bool heapPrint)
{
    //check to see of either source node or destination node is impossible
    if (s > graph -> V || s == 0)
    {
        printf("Node %d does not exist\n", s);
    }
    
    else if (t > graph -> V || t == 0)
    {
        printf("Node %d does not exist\n", t);
    }
    
    else
    {
        //vertices of graph
        int vertices = graph -> V;
        //pointer to array of distances plus mem alloc
        int *distanceArray = new int[vertices];
        //pointer to an array of parents plus mem alloc
        int *parentArray = new int[vertices];
        
        //initialize Heap, distance, and parent
        Heap *heap = initSingleSource(graph, s, distanceArray, parentArray);
        
        //until heap is empty
        while (heap -> size != 0)
        {
            //returns node NUMBER from heap
            HeapNode *extractedNode = DeleteMin(heap);
            int u = extractedNode -> vertexID;
            
//            //check to see if destination and source are equal
//            if (u == t)
//                break;
            
            //points to beginning of adjacency list
            adjacencyNode *temp = graph -> array[u].begin;
            while (temp != NULL)
            {
                int node = temp -> nodeNumber;
                relax(heap, distanceArray, parentArray, u, node, temp -> weight);
                temp = temp -> next;
            }
            
            //check to see if destination and source are equal after the heap has been completely relaxed
            if (u == t)
                break;

        }
        
        if (distanceArray[t] >= INT_MAX || distanceArray[t] < 0)
            printf("No path between node %d and node %d exists", s, t);
        
        else
        {
            //print distance and path to the node
            printf("%d\n", distanceArray[t]);
            printParents(parentArray, t, s);
            printf("\n");
            
            if (heapPrint == true)
            {
                printf("Heap: ");
                for (int i = 1; i <= heap -> size; i++)
                {
                    printf("%d ", heap -> array[i] -> vertexID);
                }
                printf("\n");
            }
        }
    }
}

Heap *initSingleSource(Graph *graph, int source, int *distanceArray, int *parentArray)
{
    Heap *heap = InitializeHeap(graph -> V);
    for (int i = 1; i <= graph -> V; i++)
    {
        heap -> array[i] = newHeapNode(i, INT_MAX);
        heap -> position[i] = i;
        distanceArray[i] = INT_MAX;
        parentArray[i] = -1;
    }
    heap -> array[source] = newHeapNode(source, distanceArray[source]);
    heap -> position[source] = source;
    distanceArray[source] = 0;
    updateDistance(heap, source, distanceArray[source]);
    heap -> size = graph -> V;
    return heap;
}

//relax
void relax(Heap *heap, int *distanceArray, int *parentArray, int u, int v, int w)
{
    int ud = distanceArray[u];
    int vd = distanceArray[v];
    
    if (vd > ud + w)
    {
        distanceArray[v] = ud + w;
        parentArray[v] = u;
        updateDistance(heap, v, distanceArray[v]);
    }
}

void printParents(int *parentArray, int t, int s)
{
    //print the distance and path!!!!
    if (t == s)
        printf("%d ", s);
    else
    {
        printParents(parentArray, parentArray[t], s);
        printf("%d ", t);
    }
}

//used to print the graph
void printGraph(Graph *myGraph)
{
    if (myGraph -> array == NULL)
    {
        cout << "Error: the graph is not initialized";
    }
    else
    {
        printf("%d %d\n", myGraph -> V, myGraph -> E);
        for (int i = 1; i <= myGraph -> V; i++)
        {
            printf("%d : ", i);
            adjacencyNode *temp = myGraph -> array[i].begin;
            while (temp != NULL)
            {
                printf("(%d %d) ", temp -> nodeNumber, temp -> weight);
                temp = temp -> next;
            }
            cout << "\n";
        }
    }
}
