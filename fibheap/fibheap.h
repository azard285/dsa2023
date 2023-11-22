#pragma once

#include <stdio.h>

typedef struct heapnode
{
    struct heapnode *parent;
    struct heapnode *left;
    struct heapnode *right;
    struct heapnode *child;
    
    int key;
    char *value;

    unsigned int degree;
    int mark;
} heapnode;

typedef struct heap
{
    heapnode *min;
    size_t nnodes;
} heap;

heap *fib_heap_create();
heapnode *fib_heap_insert(heap *heap, int key, char* value);
heap *fib_heap_union(heap *heap1, heap *heap2);
heapnode *fib_heap_extract_min(heap *heap);
int cal_degree(int nnodes);
void fib_heap_swap(heapnode *node1, heapnode *node2);
void fib_heap_consolidate(heap *heap);
void fib_heap_remove_node(heapnode *node);
void fib_heap_cut(heap *heap, heapnode *node, heapnode *parent);
void fib_heap_cascading_cut(heap *heap, heapnode *node);
void fib_heap_decrease_key(heap *heap, heapnode *node, int new_key);


// F(H) = t(H) + 2m(H)
// O() + (F(H1) - F(H))

/*
Insert:
    O(1) + ((t(H) + 1 + 2m(H)) - t(H) + 2m(H))

Min:
    O(1)

Union:
    O(1) + 0

Extract_min:
    O(t(H) + D(n)) + ((D(N) + 1 + 2m(H)) - (t(H) + 2m(H)));
    O(t(H) + D(n)) + (D(n) - t(H) + 1);
    O(t(H) + D(n))
    O(D(n));
    O(logn);


*/