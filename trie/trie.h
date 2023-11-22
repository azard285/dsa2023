#pragma once

#include "rbtree.h"

#define LEAF '$'

typedef struct trie_node {
    rb_tree *childs;

    int value;
} trie_node;

typedef struct trie {
    trie_node * root;

    char end_line;
    size_t size;
} trie;

trie *trie_create();
trie_node *trie_insert(trie *, char *, char);
trie_node *trie_lookup(trie *, char *);
void trie_delete(trie *, char *);
void trie_print(trie *);
