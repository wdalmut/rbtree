#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/rbtree.h"

#include "minunit.h"

int tests_run = 0;

static char *test_create_a_new_node() {
    leaf_t *root = rbtree_create_node(100);
    root->color = BLACK_NODE;

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Value should be 100", root->value == 100);

    return 0;
}

static char *test_insert_different_nodes() {
    leaf_t *root = rbtree_create_node(100);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 50);
    root = rbtree_put(root, 150);
    root = rbtree_put(root, 25);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be always black", root->color == BLACK_NODE);
    mu_assert("Root value should be 100", root->value == 100);
    mu_assert("Root left child should be black", root->left->color == BLACK_NODE);
    mu_assert("Root right child should be black", root->right->color == BLACK_NODE);
    mu_assert("Root left left child should be red", root->left->left->color == RED_NODE);

    return 0;
}

static char *test_rotate_to_a_new_root_from_left() {
    leaf_t *root = rbtree_create_node(1);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 2);
    root = rbtree_put(root, 3);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 2", root->value == 2);
    mu_assert("Root left child should be equals to 1", root->left->value == 1);
    mu_assert("Root right child should be equals to 3", root->right->value == 3);

    return 0;
}

static char *test_rotate_to_a_new_root_from_left_twice() {
    leaf_t *root = rbtree_create_node(1);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 2);
    root = rbtree_put(root, 3);
    root = rbtree_put(root, 4);
    root = rbtree_put(root, 5);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 2", root->value == 2);
    mu_assert("Root left child should be equals to 1", root->left->value == 1);
    mu_assert("Root right child should be equals to 3", root->right->value == 4);

    return 0;
}

static char *test_rotate_to_a_new_root_from_right_twice() {
    leaf_t *root = rbtree_create_node(5);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 4);
    root = rbtree_put(root, 3);
    root = rbtree_put(root, 2);
    root = rbtree_put(root, 1);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 2", root->value == 4);
    mu_assert("Root left child should be equals to 1", root->left->value == 2);
    mu_assert("Root right child should be equals to 3", root->right->value == 5);

    return 0;
}

static char *test_rotate_to_a_new_root_from_right_twice_and_internal_rotation() {
    leaf_t *root = rbtree_create_node(5);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 4);
    root = rbtree_put(root, 3);
    root = rbtree_put(root, 2);
    root = rbtree_put(root, 1);
    root = rbtree_put(root, 6);
    root = rbtree_put(root, 7);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 2", root->value == 4);
    mu_assert("Root left child should be equals to 1", root->left->value == 2);
    mu_assert("Root right child should be equals to 3", root->right->value == 6);
    mu_assert("Root right->left child should be equals to 5", root->right->left->value == 5);
    mu_assert("Rollback to root should give a root value of 4", root->right->left->parent->parent->value == 4);

    return 0;
}

static char *test_double_root_rotation() {
    leaf_t *root = rbtree_create_node(100);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 150);
    root = rbtree_put(root, 120);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 120", root->value == 120);
    mu_assert("Root left child should be equals to 100", root->left->value == 100);
    mu_assert("Root right child should be equals to 150", root->right->value == 150);

    return 0;
}

static char *test_rotate_to_a_new_root_from_right() {
    leaf_t *root = rbtree_create_node(3);
    root->color = BLACK_NODE;

    root = rbtree_put(root, 2);
    root = rbtree_put(root, 1);

    mu_assert("Root should not be null", root != NULL);
    mu_assert("Root should be equals to 2", root->value == 2);
    mu_assert("Root left child should be equals to 1", root->left->value == 1);
    mu_assert("Root right child should be equals to 3", root->right->value == 3);

    return 0;
}

static char *all_tests() {
    mu_run_test(test_create_a_new_node);
    mu_run_test(test_insert_different_nodes);
    mu_run_test(test_rotate_to_a_new_root_from_left);
    mu_run_test(test_rotate_to_a_new_root_from_right);
    mu_run_test(test_rotate_to_a_new_root_from_left_twice);
    mu_run_test(test_rotate_to_a_new_root_from_right_twice);
    mu_run_test(test_rotate_to_a_new_root_from_right_twice_and_internal_rotation);
    mu_run_test(test_double_root_rotation);

    return 0;
}

int main(void) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

