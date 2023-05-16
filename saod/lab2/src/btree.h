#pragma once
#define MAXWORDLENGTH 100
typedef struct Bstree
{
    int value;
    char key[MAXWORDLENGTH];
    struct Bstree *parent;
    struct Bstree *left;
    struct Bstree *right;
} Bstree;

Bstree *bstree_create(char *key, int value);
void bstree_add(Bstree *tree, char *key, int value);
Bstree *bstree_lookup(Bstree *tree, char *key);
Bstree *bstree_delete_node(Bstree *tree, Bstree *delNode);
Bstree *bstree_delete(Bstree *tree, char *key);
void ReplaceNode(Bstree *parent, Bstree *node, Bstree *child);
Bstree *bstree_min(Bstree *tree);
Bstree *bstree_max(Bstree *tree);
void PrintTree(Bstree *tree, int n);
void DeleteTree(Bstree *tree);