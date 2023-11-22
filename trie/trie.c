#include <stdio.h>

#include "trie.h"

trie_node *get_child(trie_node *node, char key) {
    if (!node) return NULL;

    rb_node *child = rbtree_lookup(node->childs, key);
    if (!child) {
        return NULL;
    }
    return (trie_node*) child->value;
}

void set_child(trie_node *node, char key, trie_node *child) {
    if (!node || !child) return;

    rbtree_insert(node->childs, key, child);
}

trie_node *trie_create_node() {
    trie_node *node = malloc(sizeof(trie_node));
    if (!node) {
        return NULL;
    }

    rb_tree *tree = rbtree_create();

    if (!tree) {
        free(node);
        return NULL;
    }

    node->childs = tree; // create red-black tree as storage for childs;
    node->value = 0;

    return node;
}

trie *trie_create() {
    trie *new = malloc(sizeof(trie));

    if (!new) { //if memory not allocated
        return NULL;
    }

    new->root = NULL;
    new->end_line = LEAF;
    new->size = 0;

    return new;
}

trie_node *trie_insert(trie *trie, char *key, char value) {
    if (!trie || !key) return NULL;

    trie_node *node = trie->root;
    if (!node) {
        node = trie_create_node();
        trie->root = node;
    }

    for (int i = 0; i < slen(key); i++) {
        trie_node *child = get_child(node, key[i]);
        if (!child) {
            child = trie_create_node();
            set_child(node, key[i], child);
        }
        node = child;
    }
    trie_node *child = trie_create_node();
    set_child(node, trie->end_line, child);
    child->value = value;
    
    return child;
}

trie_node *trie_lookup(trie *trie, char *key) {
    if (!trie || !trie->root || !key) return NULL;
    trie_node *node = trie->root;
    
    for (int i = 0; i < slen(key); i++) {
        trie_node *child = get_child(node, key[i]);
        if (!child) {
            return NULL;
        }
        node = child;
    }

    trie_node *result = get_child(node, trie->end_line);
    return result;
}

void trie_nodes_print(trie_node *trie, int level) {
    if (!trie) return;
    rbtree_print_keys(trie->childs, level);
}

void trie_print(trie *trie) {
    if (!trie) return;
    trie_nodes_print(trie->root, 0);
}

void trie_delete_dfs(trie *trie, trie_node *root, char *key, int i, int *found) {
    trie_node *child = NULL;
    if (key[i] == '\0') {
        if ((child = get_child(root, trie->end_line))) {
            *found = 1;
            rbtree_delete(root->childs, trie->end_line);
            rbtree_free(child->childs);
            free(child);
        }
            return;
    } else {
        child = get_child(root, key[i]);
        if (!child) {
            return;
        }
        trie_delete_dfs(trie, child, key, i + 1, found);
    }

    if (found) {
        if (child->childs->size == 0) {
            rbtree_delete(root->childs, key[i]);
            rbtree_free(child->childs);
            free(child);
        } else {
            *found = 0;
        }
    }
}

void trie_delete(trie *trie, char *key) {
    if (!trie) return;

    int found = 0;
    trie_delete_dfs(trie, trie->root, key, 0, &found);
}
