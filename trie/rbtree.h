#pragma once
#include <stdlib.h>

enum COLOR {
    RED,
    BLACK
};

typedef struct rb_node{
    void *value;
    char key;
    enum COLOR color;

    struct rb_node *left;
    struct rb_node *right;
    struct rb_node *parent;
} rb_node;

typedef struct {
    rb_node* root;
    rb_node* null;
    size_t size;
} rb_tree;

rb_tree *rbtree_create();
rb_node *rbtree_lookup(rb_tree *, char);
rb_node *rbtree_insert(rb_tree *, char, void *);
void rbtree_delete(rb_tree *, char);
void rbtree_free(rb_tree *);
void rbtree_print_tree(rb_tree *);
rb_node *rbtree_min(rb_tree *, rb_node *);
rb_node *rbtree_max(rb_tree *, rb_node *);
int rbtree_check_height(rb_tree *);
void rbtree_print_keys(rb_tree *, int);

int slen(char *);