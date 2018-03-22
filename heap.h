//
//  heap.h
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#ifndef heap_h
#define heap_h
#include <stdio.h>

struct HeapNode
{
    int key;
    int vertexID;
};

struct Heap
{
    int capacity;
    int size;
    int *position;
    struct HeapNode **array;
};

Heap *InitializeHeap(int n);
HeapNode *newHeapNode(int vertexID, int key);
void swapHeapNodes(HeapNode **first, HeapNode **second);
HeapNode *newHeapNode(int nodeNumber, int weight);
HeapNode *DeleteMin(Heap *heap);
void updateDistance(Heap *heap, int heapNode, int newKey);

#endif /* heap_h */
