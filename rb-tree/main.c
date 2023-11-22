#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "rbtree.h"

#define SORTED_WORDS_FILE "sorted_words"
#define WORDS 50000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void get_sorted_words(char **words, size_t size)
{
    FILE *file = fopen(SORTED_WORDS_FILE, "r");
    for (int i = 0; i < size; i++) {
        words[i] = (char*) malloc(sizeof(char) * 100);
        fgets(words[i], 100,file);
    }
}

int main() {
    rb_tree *tree = rbtree_create();
    assert((tree != NULL) && "Memory for tree not allocated\n");

    char **words = (char**) malloc(WORDS * sizeof(char*));
    assert((words != NULL) && "Memory for 'words' not allocated\n");

    get_sorted_words(words, WORDS);

    for (int i = 0; i < WORDS; i++) {
        rbtree_insert(tree, words[i], i);
        if ((i + 1) % 1000 == 0) {
            double lookup_time = wtime();
            for (int k = 0; k < 100000; k++) {
                rbtree_lookup(tree, words[i]);
            }
            lookup_time = (wtime() - lookup_time);
            printf("%d;%lf\n", i + 1, lookup_time);
        }
    }

    for (int i = 0; i < WORDS; i++) {
        rbtree_delete(tree, words[i]);
    }

    // printf("%d\n", rbtree_check_height(tree));

    // rbtree_print_tree(tree);

    // rbtree_delete(tree, "1-aachen");

    // printf("\n\n\n");
    // rbtree_print_tree(tree);

    // rbtree_free(tree);

    // for (int i = 0; i < WORDS; i++) {
    //     printf("%d\n", i);
    //     free(words[i]);
    // }
    free(words);

    return 0;
}
