#include <stdlib.h>
#include <stdio.h>

#include "fibheap.h"

int main() {
    heap *h = fib_heap_create();

    for (int i = 0; i < 10; i++) {
        fib_heap_insert(h, i, "hello");
    }

    fib_heap_insert(h, -99, "hello");

    for (int i = 0; i < 10; i++) {
        heapnode *node = fib_heap_extract_min(h);
        printf("%d\n", node->key);
    }

    free(h);
    return 0;
}