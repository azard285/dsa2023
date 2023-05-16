#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "btree.h"
#include "hashtab.h"
#define COUNTWORDS 10
Listnode *hashtab[HASHTAB_SIZE];

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double res = (double)t.tv_sec + (double)t.tv_usec * 1E-6;
    return res;
}
int getRand(int min, int max)
{
    return min + rand() % max;
}
int main()
{
    srand(time(NULL));

    /*Код, демонстрирующий работу бинарного дерева
    Bstree *tree = bstree_create("hello", 24);
    Bstree *max;
    Bstree *min;
    bstree_add(tree, "good", 677);
    bstree_add(tree, "bye", 129);
    bstree_add(tree, "car", 645);
    bstree_add(tree, "hi", 678);
    bstree_add(tree, "dog", 999);

    if (bstree_lookup(tree, "hi") != NULL)
        printf("%s: %d\n", bstree_lookup(tree, "hi")->key, bstree_lookup(tree, "hi")->value);
    else
        printf("Node not found\n");

    max = bstree_min(tree);
    min = bstree_max(tree);
    PrintTree(tree, 10);
    printf("MAX: %s: %d\n", max->key, max->value);
    printf("MIN: %s: %d\n", min->key, min->value);

    Bstree *newTree;
    newTree = bstree_delete(tree, "bye");
    PrintTree(newTree, 10);
    DeleteTree(newTree);
    */

    /*Код, демонстрирующий работу хэш-таблицы
    Listnode *node;

    hashtab_init(hashtab);
    hashtab_add(hashtab, "Ocelot", 17);
    hashtab_add(hashtab, "Flamingo", 4);
    hashtab_add(hashtab, "Fox", 14);
    node = hashtab_lookup(hashtab, "Flamingo");
    if (node != NULL)
        printf("Node: %s, %d\n", node->key, node->value);

    hashtab_delete(hashtab, "Ocelot");
    node = hashtab_lookup(hashtab, "Ocelot");
    if (node != NULL)
        printf("Node: %s, %d\n", node->key, node->value);
    else
        printf("Node not found\n");
    */

    char **words = (char **)malloc(sizeof(char *));
    FILE *f;
    f = fopen("unordered.txt", "r");
    if (f == NULL)
        printf("ERROR");

    int n = 0;
    while (!feof(f))
    {
        words[n] = (char *)malloc(sizeof(char) * 256);
        fgets(words[n], 256, f);
        n++;
        words = (char **)realloc(words, sizeof(char *) * (n + 1));
    }
    fclose(f);
    Bstree *tree = bstree_create(words[0], 0);
    Listnode *nodeH;

    hashtab_init(hashtab);
    double t;
    char *w;
    char *resWordArray[100];
    Bstree *nodeB;

    // Задание 1
    for (int i = 2; i < n + 1; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            for (size_t j = 0; j < 100; j++)
            {
                w = words[getRand(0, i - 1)];
                resWordArray[j] = w;
            }

            t = wtime();
            for (size_t j = 0; j < 100; j++)
            {
                nodeB = bstree_lookup(tree, resWordArray[j]);
            }
            t = wtime() - t;
            printf("Bstree: n = %d; time = %.6lf", i, t);

            t = wtime();
            for (size_t j = 0; j < 100; j++)
            {
                nodeH = hashtab_lookup(hashtab, resWordArray[j]);
            }
            t = wtime() - t;
            printf("                                        Hashtab: n = %d; time = %.6lf\n", i, t);
        }
    }
    

    /*// Задание 2
    for (int i = 2; i < n + 1; i++)
    {
        bstree_add(tree, words[i - 1], i - 1);

        if (i % 10000 == 0)
        {
            t = wtime();
            nodeH = bstree_max(tree);
            t = wtime() - t;
            printf("Bstree max: n = %d; time = %.6lf\n", i, t);
        }
    }*/

    // Освобождение памяти для задания 1 и 2
    for (int i = 0; i < n; i++)
    {
        free(words[i]);
    }
    free(words);

    /*Задание 3
     int collision;
     Listnode *temp;

     for (int i = 2; i < n + 1; i++)
     {
         hashtab_add(hashtab, words[i - 1], i - 1);
         if (i % 10000 == 0)
         {
             collision = 0;
             temp = NULL;
             // w = words[getRand(0, i - 1)];
             t = wtime();
             for (size_t j = 0; j < 100; j++)
             {
                 w = words[getRand(0, i - 1)];
                 nodeH = hashtab_lookup(hashtab, w);
             }
             t = wtime() - t;
             printf("Hashtab: n = %d; time = %.6lf", i, t);

             // Все ломает
             for (int j = 0; j < HASHTAB_SIZE; j++)
             {
                 if (hashtab[j] == NULL)
                 {
                     continue;
                 }
                 for (temp = hashtab[j]->next; temp != NULL; temp = temp->next)
                 {
                     collision++;
                 }
             }
             printf("   Collision: %d\n", collision);
         }
     }
     */
    return 0;
}