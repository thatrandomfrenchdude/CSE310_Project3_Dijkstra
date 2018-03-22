//
//  util.h
//  Project03
//
//  Created by Nicholas Debeurre on 4/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#ifndef util_h
#define util_h
#include <stdio.h>

void heapify(Heap *heap, int i);
bool nodeExists(Heap *heap, int index);
int parent(int i);
int left(int i);
int right(int i);
void flush();

#endif /* util_h */
