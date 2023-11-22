#include <stdio.h>

#include "trie.h"

int main() {
    trie *trie = trie_create();
    char *ch = "matrix";
    trie_insert(trie, ch, 59);
    // char *ch1 = "minus";
    // trie_insert(trie, ch1, 5);
    // char *ch2 = "minumum";
    // trie_insert(trie, ch2, 55);
    // char *ch3 = "plus"; 
    // trie_insert(trie, ch3, 91); 
    // char *ch4 = "c++"; 
    // trie_insert(trie, ch4, 65); 
    // char *ch5 = "c++"; 
    // trie_insert(trie, ch5, 98); 
    // trie_print(trie);

    char *ch6 = "matrix";
    trie_delete(trie, ch6);
    // if (node) {
    //     printf("%s: %d\n", ch6, node->value);
    // }

    return 0;
}

//O(mlogd)
//O(mlogn)