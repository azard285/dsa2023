#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"
Bstree *bstree_create(char *key, int value)
{
    Bstree *node = malloc(sizeof(*node));
    if (node != NULL)
    {
        if (strlen(key) < MAXWORDLENGTH)
            strcpy(node->key, key);
        else
            return NULL;
        node->value = value;
        node->parent = NULL;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
void bstree_add(Bstree *tree, char *key, int value)
{
    if (tree == NULL)
        return;
    Bstree *parent, *node;
    while (tree != NULL) // Идет вниз по дереву до NULL, назначает ноду перента
    {
        parent = tree;
        if (strcmp(key, tree->key) < 0) // Если слово меньше, то влево
            tree = tree->left;
        else if (strcmp(key, tree->key) > 0) // Если слово больше, то вправо
            tree = tree->right;
        else // если слова идентичны(strcmp(key, tree->key) == 0), то вернуть NULL, т.к. не может быть повторов
            return;
    }

    node = bstree_create(key, value); // Создание нода
    node->parent = parent;
    if (strcmp(key, parent->key) < 0) // Присваивание потомка правому или левому узлу родителя
        parent->left = node;
    else
        parent->right = node;
}
Bstree *bstree_lookup(Bstree *tree, char *key) // Ищет узел по ключу
{
    while (tree != NULL)
    {
        if (strcmp(key, tree->key) == 0)
            return tree;
        else if (strcmp(key, tree->key) < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

// Может быть 4 случая:
//  когда у удаляемого узла нет ни левого, ни правого потомка(автоматически выполняется при проверке второго условия)
//  Когда у удаляемого узла нет левого потомка
//  Когда у удаляемого узла нет правого потомка
//  И когда у удаляемого узла есть и левый и правый
Bstree *bstree_delete_node(Bstree *tree, Bstree *delNode)
{
    if (delNode->left == NULL)
    {
        ReplaceNode(delNode->parent, delNode, delNode->right);
        if (delNode->parent == NULL) // Если удаляемый элемент корень
            tree = delNode->right;
    }
    else if (delNode->right == NULL)
    {
        ReplaceNode(delNode->parent, delNode, delNode->left);
        if (delNode->parent == NULL) // Если удаляемый элемент корень
            tree = delNode->left;
    }
    else
    {
        Bstree *min = delNode->right;
        Bstree *minParent = min;
        while (min->left != NULL)
        {
            minParent = min;
            min = min->left;
        }
        ReplaceNode(delNode->parent, delNode, min);
        if (delNode->parent == NULL)
            tree = min;
        if (delNode->right != NULL)
        {
            minParent->left = min->right;
            min->left = delNode->left;
            min->right = delNode->right;
        }
        else
            min->left = delNode->left;
    }
    free(delNode);
    return tree;
}
void ReplaceNode(Bstree *parent, Bstree *node, Bstree *child)
{
    if (parent != NULL)
    {
        if (strcmp(node->key, parent->key) < 0)
            parent->left = child;
        else
            parent->right = child;
    }
}
Bstree *bstree_delete(Bstree *tree, char *key)
{
    Bstree *delNode;
    if ((delNode = bstree_lookup(tree, key)) == NULL)
        return NULL;
    return bstree_delete_node(tree, delNode);
}

// Самый минимльный элемент находится
// в нижним левом углу
Bstree *bstree_min(Bstree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;

    return tree;
}
Bstree *bstree_max(Bstree *tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;

    return tree;
}
void PrintTree(Bstree *tree, int n)
{
    if (tree == NULL)
        return;

    if (tree->right)
    {
        PrintTree(tree->right, n + 15);
    }

    for (int i = 0; i < n; i++)
        printf(" ");

    printf("%s: %d\n", tree->key, tree->value);

    if (tree->left)
    {
        PrintTree(tree->left, n + 15);
    }
}
void DeleteTree(Bstree *tree)
{
    if (tree != NULL)
    {
        DeleteTree(tree->left);
        DeleteTree(tree->right);
        free(tree);
    }
}
