//
//  heap.cpp
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <array>
#include <cmath>
#include "main.h"
#include "heap.h"
#include "graph.h"
#include "util.h"

using namespace std;

//initializes a heap for use
//working
Heap *InitializeHeap(int capacity)
{
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    try
    {
        heap -> capacity = capacity;
        heap -> size = 0;
        heap -> position = (int*)malloc((capacity + 1) * sizeof(int));
        heap -> array = (HeapNode**)malloc((capacity + 1) * (sizeof(HeapNode*)));
    }
    catch (std::bad_alloc bae)
    {
        cout << "\nError: Heap cannot allocate enough memory for n\n";
        heap = NULL;
    }
    return heap;
}

HeapNode *newHeapNode(int vertexID, int key)
{
    HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode));
    node -> key = key;
    node -> vertexID = vertexID;
    return node;
}

void swapHeapNodes(HeapNode **first, HeapNode **second)
{
    HeapNode *node = *first;
    *first = *second;
    *second = node;
}

//deletes the minimum value from the heap
//working
HeapNode *DeleteMin(Heap *heap)
{
    if (heap -> size == 0)
    {
        cout << "Error: Heap has no nodes";
        return NULL;
    }
    else
    {
        //saves root node and swaps last node to front
        HeapNode *rootNode = heap -> array[1];
        HeapNode *lastNode = heap -> array[heap -> size];
        heap -> array[1] = lastNode;
        
        //fix positions
        heap -> position[rootNode -> vertexID] = heap -> size;
        heap -> position[lastNode -> vertexID] = 1;
        
        //"cuts off" the last node
        heap -> size--;
        
        //heapifies the heap to maintain heap order
        heapify(heap, 1);
        
        //returns min
        return rootNode;
    }
}

//updates the distance
//working
void updateDistance(Heap *heap, int heapNode, int newKey)
{
    if (newKey > heap -> array[heap -> position[heapNode]] -> key)
        return;
    
    else
    {
        //get the index of the vertex in the heap
        int index = heap -> position[heapNode];
        
        //update key
        heap -> array[index] -> key = newKey;
        
        while (index > 1 && heap -> array[index] -> key < heap -> array[parent(index)] -> key)
        {
            heap -> position[heap -> array[index] -> vertexID] = parent(index);
            heap -> position[heap -> array[parent(index)] -> vertexID] = index;
            swapHeapNodes(&heap -> array[index], &heap -> array[parent(index)]);
            index = parent(index);
        }
    }
}
