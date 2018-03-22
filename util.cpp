//
//  util.cpp
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "main.h"
#include "heap.h"
#include "graph.h"
#include "util.h"

using namespace std;

//used to heapify the inputted heap at the given point
void heapify(Heap *heap, int i)
{
    int lChild = left(i);
    int rChild = right(i);
    int smallest;
    
    if ((lChild <= heap -> size) && (heap -> array[lChild] -> key < heap -> array[i] -> key))
        smallest = lChild;
    else
        smallest = i;
    
    if ((rChild <= heap -> size) && (heap -> array[rChild] -> key < heap -> array[smallest] -> key))
        smallest = rChild;
    
    if (smallest != i)
    {
        //identify nodes to swap, update positions, swap nodes
        HeapNode *small = heap -> array[smallest];
        HeapNode *tempNode = heap -> array[i];
        heap -> position[small -> vertexID] = i;
        heap -> position[tempNode -> vertexID] = smallest;
        swapHeapNodes(&heap -> array[smallest], &heap -> array[i]);
        
        //recursively calls heapify again
        heapify(heap, smallest);
    }
}

bool nodeExists(Heap *heap, int index)
{
    if (heap -> position[index] < heap -> size)
        return true;
    else
        return false;
}

//used  to find t he parent of a selected index
int parent(int i)
{
    return (int)(i/2);
}

//used to find the left child of a selected index
int left(int i)
{
    return (2*i);
}

//used to find the right child of a selected index
int right(int i)
{
    return ((2*i)+1);
}

void flush()
{
    int c;
    do c = getchar(); while (c != '\n' && c != EOF);
}
