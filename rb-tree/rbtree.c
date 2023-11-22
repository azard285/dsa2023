#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "rbtree.h"

rb_node *rbtree_node_create(char *key, int value) {
    rb_node *node = malloc(sizeof(rb_node));
    node->key = key;
    node->value = value;
    node->color = RED;
    node->parent = node->left = node->right = NULL;
    return node;
}

rb_tree *rbtree_create() {
    rb_tree *tree = malloc(sizeof(rb_tree));
    tree->size = 0;
    tree->null = rbtree_node_create(0, 0);
    tree->null->color = BLACK;
    tree->root = tree->null;
    return tree;
}

void rbtree_rotate_left(rb_tree *tree, rb_node *x) {
    if (!x) return;
    rb_node* y = x->right;
    x->right = y->left;

    if (y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        tree->root = y;
    }

    y->left = x;
    x->parent = y;
}

void rbtree_rotate_right(rb_tree *tree, rb_node *x) {
    if (!x) return;

    rb_node* y = x->left;
    x->left = y->right;

    if (y->right) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        } 
    } else {
        tree->root = y;
    }
    y->right = x;
    x->parent = y;
}

void rbtree_insert_fix_up(rb_tree *tree,  rb_node *node) {
    if (!node) return;
    while (node != tree->root && node->parent != tree->root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) { // 1, 2,3 cases
            rb_node* u = node->parent->parent->right;
            if (u && u->color == RED) { // case 1
                node->parent->color = BLACK;
                u->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) { //case2
                    node = node->parent;
                    rbtree_rotate_left(tree, node); //case2 => case3
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbtree_rotate_right(tree, node->parent->parent); //case 3
            }
        } else {                                        // 3, 4, 5 cases
            rb_node* u = node->parent->parent->left;
            if (u && u->color == RED) { //case 4
                node->parent->color = BLACK;
                u->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) { //case 5
                    node = node->parent;
                    rbtree_rotate_right(tree, node); //case 5 => case 6 
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rbtree_rotate_left(tree, node->parent->parent); //case 6
            }
        }
    }
    tree->root->color = BLACK;
}

rb_node *rbtree_insert(rb_tree *tree, char *key, int value) {
    rb_node *root = tree->root;
    rb_node *parent = NULL;
    while (root != tree->null) {
        parent = root;
        int compare = strcmp(key, parent->key);
        if (compare > 0) {
            root = root->right;
        } else if (compare < 0) {
            root = root->left;
        } else return NULL;
    }
    
    rb_node *new_node = rbtree_node_create(key, value);
    if (!new_node) {
        return NULL;
    }

    new_node->left = new_node->right = tree->null;

    if (!parent) {
        tree->root = new_node;
        return NULL;
    }
    
    int compare = strcmp(key, parent->key);
    if (compare > 0) {
        parent->right = new_node;
    } else if (compare < 0){
        parent->left = new_node;
    }

    tree->size++;
    new_node->parent = parent;
    rbtree_insert_fix_up(tree, new_node);
    return new_node;
}

rb_node *rbtree_lookup(rb_tree *tree, char* key) {
    rb_node *node = tree->root;

    while (node != tree->null) {
        int compare = strcmp(key, node->key);
        if (compare > 0) {
            node = node->right;
        } else if (compare < 0) {
            node = node->left;
        } else {
            return node == tree->null ? NULL : node;
        }
    }
    return NULL;
}

rb_node *rbtree_min(rb_tree *tree, rb_node *sub_tree) {
    rb_node *node = sub_tree;

    if (node == tree->null) {
        return tree->null;
    }

    while (node->left != tree->null) {
        node = node->left;
    }
    return node;
}

rb_node *rbtree_max(rb_tree *tree, rb_node *sub_tree) {
    rb_node *node = sub_tree;

    if (node == tree->null) {
        return tree->null;
    }

    while (node->right != tree->null) {
        node = node->right;
    }
    return node;
}

void rbtree_transplant(rb_tree *tree, rb_node* n1, rb_node *n2) {
    if (!n1->parent) {
        tree->root = n2;
    } else if (n1 == n1->parent->left) {
        n1->parent->left = n2;
    } else {
        n1->parent->right = n2;
    }
    if (n2) {
        n2->parent = n1->parent;
    }
}

void rbtreee_delete_fix_up(rb_tree* tree, rb_node* node) {
    while (node != tree->root && node->color == BLACK) {
        if (node == node->parent->left) {
            rb_node* brother = node->parent->right;
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rbtree_rotate_left(tree, node->parent);
                brother = node->parent->right;
            }
            if ((brother->left->color == BLACK) &&
                (brother->right->color == BLACK)) {
                    brother->color = RED;
                    node = node->parent;
            } else {
                if (brother->right->color == BLACK) {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rbtree_rotate_right(tree, brother);
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                rbtree_rotate_left(tree, node->parent);
                node = tree->root;
            }
        } else {
            rb_node* brother = node->parent->left;
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rbtree_rotate_right(tree, node->parent);
                brother = node->parent->left;
            }
            if ((brother->left->color == BLACK) &&
                (brother->right->color == BLACK)) {
                    brother->color = RED;
                    node = node->parent;
            } else {
                if (brother->left->color == BLACK) {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    rbtree_rotate_left(tree, brother);
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->left->color = BLACK;
                rbtree_rotate_right(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

void rbtree_delete(rb_tree *tree, char *key) {
    rb_node *node = rbtree_lookup(tree, key); //find node for delete

    if (!node) {
        return ;
    }

    rb_node *y = node;
    rb_node *x = node;
    rb_node *y_parent = y->parent;
    int ycolor = node->color;

    if (node->left == tree->null) {
        x = node->right;
        rbtree_transplant(tree, node, node->right);
    } else if (node->right == tree->null) {
        x = node->left;
        rbtree_transplant(tree, node, node->left);
    } else {
        y = rbtree_min(tree, node->right);
        y_parent = y->parent;
        ycolor = y->color;
        x = y->right;

        if (x) {
            rbtree_transplant(tree, y, x);
        }
        y->right = node->right;
        y->right->parent = y;
        rbtree_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    
    if (ycolor == BLACK) {
        if (x == tree->null) {
            x->parent = y_parent;
        }
        rbtreee_delete_fix_up(tree, x);
        tree->null->parent = NULL;
        free(node->key);
        free(node);
    }
}

void rbtree_delete_node(rb_node *root) {
    if (!root) return;

    rbtree_delete_node(root->left);
    rbtree_delete_node(root->right);
    free(root->key);
    free(root);

}

void rbtree_free(rb_tree *tree) {
    if (!tree) return;

    rbtree_delete_node(tree->root);
    free(tree);
}

void rbtree_print_node(rb_tree *tree, rb_node *node, int h) {
    if (node == tree->null) return;
    
    rbtree_print_node(tree, node->left, h + 1);
    for (int i = 0; i < h; i++) {
        printf("\t");
    }
    printf("%d-%s\n", node->color, node->key);

    rbtree_print_node(tree, node->right, h + 1);

}

void rbtree_print_tree(rb_tree *tree) {
    rbtree_print_node(tree, tree->root, 0);
}

int rbtree_get_height(rb_node *node) {
    if (!node) return 0;
    if (node->color == BLACK) {
        return 1 + rbtree_get_height(node->right);
    }
    return rbtree_get_height(node->right);
}

int rbtree_check_height_node(rb_node *node) {
    if (!node) return 0;
    if (rbtree_check_height_node(node->left) == -1 || rbtree_check_height_node(node->right) == -1) {
        return -1;
    }
    if (rbtree_get_height(node->left) != rbtree_get_height(node->right)) {
        return -1;
    }
    return 0;
}

int rbtree_check_height(rb_tree *tree) {
    return rbtree_check_height_node(tree->root);
}


/*
h < 2log2(n + 1)

bh(x)

2^bh(x) - 1;
2^0 - 1 = 1 - 1 = 0;

(2^(bh(x) - 1) - 1) + (2^(bh(x) - 1) - 1) + 1 = 2^bh(x) - 1;

n >= 2^bh(x) - 1;
n + 1 >= 2^bh(x);
log_2(n + 1) >= bh(x);

log_2(n + 1) >= h/2;
2 log_2(n + 1) >= h;

h/2 <= bh(x);

*/