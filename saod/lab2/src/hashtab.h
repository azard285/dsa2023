#pragma once
#define HASHTAB_SIZE 50051
typedef struct listnode {
    char *key;
    int value;

    struct listnode *next;
} Listnode;



unsigned int hashtab_hash(char *key);
void hashtab_init(Listnode **hashtab);
void hashtab_add(Listnode **hashtab, char *key, int value);
Listnode *hashtab_lookup(Listnode **hashtab, char *key);
void hashtab_delete(Listnode **hashtab, char *key);