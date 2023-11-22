#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#include "fibheap.h"

heap *fib_heap_create()
{
    heap *h = calloc(1, sizeof(heap));
    h->min = NULL;
    h->nnodes = 0;
    return h;
}

void fib_heap_link_list(heapnode *heap1min, heapnode *heap2min)
{
    if (!heap1min || !heap2min) {
        return ;
    }
    heapnode *left1 = heap1min->left;
    heapnode *left2 = heap2min->left;
    left1->right = heap2min;
    heap2min->left = left1;
    heap1min->left = left2;
    left2->right = heap1min;
}

void fib_heap_add_node_to_root_list(heapnode *node, heapnode *minnode)
{
    if (!minnode || !node) {
        return;
    }
    if (node == minnode) {
        return ;
    }

    if (minnode == minnode->right) {
        node->left = minnode;
        node->right = minnode;
        minnode->left = node;
        minnode->right = node;
        
    } else {
        heapnode *lnode = minnode->left;
        minnode->left = node;
        node->right = minnode;
        node->left = lnode;
        lnode->right = node;
    }
}

void fib_heap_link(heap *heap, heapnode *node1, heapnode *node2)
{
    if (!heap || !node1 || !node2) {
        return ;
    }

    fib_heap_remove_node(node1);
    // if (node2->right == node2) {
    //     heap->min = node2;
    // }

    node1->parent = node2;
    if (!node2->child) {
        node2->child = node1;
    } else {
        fib_heap_add_node_to_root_list(node1, node2->child);
    }

    node2->degree++;
    node1->mark = 0;
}

heapnode *fib_heap_insert(heap *heap, int key, char* value)
{
    if (!heap) {
        return NULL;
    }
    heapnode *node = malloc(sizeof(heapnode));

    if (!node) {
        return NULL;
    }

    node->value = malloc(sizeof(char) * (strlen(value) + 1));
    if (!node->value) {
        free(node);
        return NULL;
    }

    strcpy(node->value, value);
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->left = node;
    node->right = node;
    node->parent = NULL;
    node->child = NULL;

    fib_heap_add_node_to_root_list(node, heap->min);
    if (!heap->min || node->key < heap->min->key) {
        heap->min = node;
    }
    heap->nnodes++;

    return node;
}

heap *fib_heap_union(heap *heap1, heap *heap2)
{
    if (!heap1 || !heap2) {
        return NULL;
    }

    heap *res_heap = fib_heap_create();
    res_heap->min = heap1->min;
    fib_heap_link_list(heap1->min, heap2->min);
    if (!heap1->min || (heap2->min && heap1->min > heap2->min)) {
        res_heap->min = heap2->min;
    }
    res_heap->nnodes = heap1->nnodes + heap2->nnodes;
    free(heap1);
    free(heap2);

    return res_heap;
}

void fib_heap_remove_node(heapnode *node)
{
    if (!node) {
        return ;
    }

    if (node == node->right) {
        return ;
    }

    node->right->left = node->left;
    node->left->right = node->right;
    node->left = node->right = node;
}

heapnode *fib_heap_extract_min(heap *heap)
{
    if (!heap) {
        return NULL;
    }
    heapnode *min = heap->min;
    if (min) {
        if (min->child) {
            heapnode *x = min->child;
            heapnode *next = x->right;
            for (int i = 0; i < min->degree; i++){
                fib_heap_remove_node(x);
                fib_heap_add_node_to_root_list(x, heap->min);

                x->parent = NULL;
                x = next;
                next = next->right;
            }
        }

        if (min == min->right) {
            heap->min = NULL;
        } else {
            heap->min = min->right;
        }
        fib_heap_remove_node(min);

        if (heap->min) {
            fib_heap_consolidate(heap);
        }

        heap->nnodes--;
    }
    return min;
}

int cal_degree(int nnodes)
{
  return floor(log2(nnodes) + 1);
}

void fib_heap_swap(heapnode *node1, heapnode *node2)
{
    if (!node1 || !node2) {
        return ;
    }
    heapnode *lnode1 = node1->left;
    heapnode *rnode1 = node1->right;
    node1->left = node2->left;
    node1->right = node2->right;
    node2->left = lnode1;
    node2->right = rnode1;
}

void fib_heap_consolidate(heap *heap)
{
    if (!heap) {
        return ;
    }
    int max_d = cal_degree(heap->nnodes);
    int num_roots = 0;
    heapnode **A = calloc(max_d + 1, sizeof(heapnode*));
    heapnode *x = heap->min;

    if (x) {
        num_roots++;
        x = x->right;

        while (x != heap->min) {
            num_roots++;
            x = x->right;
        }
    } else {
        return ;
    }

    for (int i = 0; i <= max_d; i++) {
        A[i] = NULL;
    }
    
    heapnode *next = x, *y;
    while (num_roots > 0) {
        int d = x->degree;
        next = next->right;

        while (A[d]) {
            y = A[d];
            if (x->key > y->key) {
                heapnode *tmp = x;
                x = y;
                y = tmp;
            }
            fib_heap_link(heap, y, x);

            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = next;
        num_roots--;
    }

    heap->min = NULL;

    for (int i = 0; i <= cal_degree(heap->nnodes); i++) {
        if (A[i]) {
            if (!heap->min) {
                heap->min = A[i];
            } else {
                fib_heap_remove_node(A[i]);
                fib_heap_add_node_to_root_list(A[i], heap->min);
            }
            if (A[i]->key < heap->min->key) {
                heap->min = A[i];
            }   
        }
    }
    free(A);
}

void fib_heap_cut(heap *heap, heapnode *node, heapnode *parent)
{
    if (!heap || !node || !parent) {
        return ;
    }

    parent->child = (node == node->right ? NULL: node->right);
    fib_heap_remove_node(node);
    parent->degree--;

    fib_heap_add_node_to_root_list(node, heap->min);

    node->parent = NULL;
    node->mark = 0;
}

void fib_heap_cascading_cut(heap *heap, heapnode *node)
{
    if (!heap || !node) {
        return ;
    }

    heapnode *parent = node->parent;
    if (!parent) {
        return ;
    }

    if (!node->mark) {
        node->mark = 1;
    } else {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
}

void fib_heap_decrease_key(heap *heap, heapnode *node, int new_key)
{
    if (!node || !heap || !heap->min) {
        return ;
    }
    if (new_key >= node->key) {
        return ;
    }

    node->key = new_key;
    heapnode *parent = node->parent;
    if (parent && node->key < parent->key) {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    if (node->key < heap->min->key) {
        heap->min = node;
    }
}

void fib_heap_delete(heap *heap, heapnode *node)
{
    if (!heap || !node) {
        return ;
    }
    fib_heap_decrease_key(heap, node, INT_MIN);
    fib_heap_extract_min(heap);
}
