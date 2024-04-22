#include "rbtree.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    rbtree_insert(t, 10);
    rbtree_insert(t, 5);
    rbtree_insert(t, 30);
    rbtree_insert(t, 45);
    rbtree_insert(t, 25);
    rbtree_insert(t, 35);
    rbtree_insert(t, 1);
    rbtree_insert(t, 3);
    rbtree_insert(t, 7);
    //left_rotation(t, t->root);
    // right_rotation(t, t->root);
    printf("find 결과: %p\n", rbtree_find(t, 45));
    printf("max 결과: %p\n", rbtree_max(t));
    printf("min 결과: %p\n", rbtree_min(t));
    // printf("root 값: %d\n", t->root->key);
    // printf("right 값: %d\n", t->root->right->key);
    // printf("right->right값: %d\n", t->root->right->right->key);

    // printf("right 값: %d\n", t->root->right->key);
    // printf("right->right값: %d\n", t->root->right->right->key);
    // printf("right->left값: %d\n", t->root->right->left->key);
    // printf("right->right->left값: %d\n", t->root->right->right->left->key);
}