#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtab.h"

unsigned int JenkinsHash(char *s)
{
    unsigned int h = 0;
    while (*s)
    {
        h += (unsigned int)*s++;
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h % HASHTAB_SIZE;
}
unsigned int hashtab_hash(char *key) // KRHash
{
    unsigned int h = 0, hash_mul = 31;
    while (*key)
        h = h * hash_mul + (unsigned int)*key++;
    return h % HASHTAB_SIZE;
}
void hashtab_init(Listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}
void hashtab_add(Listnode **hashtab, char *key, int value)
{
    Listnode *node;

    int index = hashtab_hash(key);
    node = malloc(sizeof(*node));

    if (node != NULL)
    {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}
Listnode *hashtab_lookup(Listnode **hashtab, char *key)
{
    Listnode *node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) // Идем по связонному списку, ищем нужное значение
    {
        if (0 == strcmp(node->key, key))
            return node;
    }
    return NULL;
}
void hashtab_delete(Listnode **hashtab, char *key)
{
    Listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        if (0 == strcmp(node->key, key))
        {
            if (prev == NULL)
                hashtab[index] = node->next; // Если первый элемент?
            else
                prev->next = node->next;
            free(node);
            return;
        }
        prev = node;
    }
}