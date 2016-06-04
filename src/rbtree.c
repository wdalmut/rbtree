#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

static void rbtree_put_node(leaf_t *, leaf_t *);

// cases
static leaf_t *rbtree_case_1(leaf_t *);
static leaf_t *rbtree_case_2(leaf_t *);
static leaf_t *rbtree_case_3(leaf_t *);
static leaf_t *rbtree_case_4(leaf_t *);
static leaf_t *rbtree_case_5(leaf_t *);

// helpers
static leaf_t *rbtree_grandfather(leaf_t *);
static leaf_t *rbtree_uncle(leaf_t *);
static void rbtree_rotate_left(leaf_t *);
static void rbtree_rotate_right(leaf_t *);

static leaf_t *rbtree_uncle(leaf_t *node)
{
    leaf_t *uncle = NULL;

    leaf_t *old = rbtree_grandfather(node);

    if (old != NULL) {
        if (old->left == node->parent) {
            uncle = old->right;
        } else {
            uncle = old->left;
        }
    }

    return uncle;
}

static leaf_t *rbtree_grandfather(leaf_t *node)
{
    leaf_t *gp = NULL;

    if (node->parent != NULL && node->parent->parent != NULL) {
        gp = node->parent->parent;
    }

    return gp;
}

leaf_t *rbtree_put(leaf_t *root, int value)
{
    leaf_t *node = rbtree_create_node(value);
    rbtree_put_node(root, node);

    leaf_t *new_root = rbtree_case_1(node);

    return (new_root && new_root->parent == NULL) ? new_root : root;
}

static leaf_t *rbtree_case_1(leaf_t *node)
{
    if (node->parent == NULL) {
        node->color = BLACK_NODE;
        node = NULL;
    } else {
        node = rbtree_case_2(node);
    }

    return node;
}

static leaf_t *rbtree_case_2(leaf_t *node)
{
    if (node->parent->color != BLACK_NODE) {
        return rbtree_case_3(node);
    }
    return NULL;
}

static leaf_t *rbtree_case_3(leaf_t *node)
{
    leaf_t *uncle = rbtree_uncle(node);

    if (uncle != NULL && uncle->color == RED_NODE && node->parent->color == RED_NODE) {
        leaf_t *old = rbtree_grandfather(node);
        old->color = RED_NODE;
        uncle->color = BLACK_NODE;
        node->parent->color = BLACK_NODE;
        return rbtree_case_1(old);
    } else {
        return rbtree_case_4(node);
    }
}

static leaf_t *rbtree_case_4(leaf_t *node)
{
    leaf_t *old = rbtree_grandfather(node);

    if ((node == node->parent->right) && (node->parent == old->left)) {
        rbtree_rotate_left(node->parent);
        node = node->left;
    } else if ((node == node->parent->left) && (node->parent == old->right)) {
        rbtree_rotate_right(node->parent);
        node = node->right;
    }

    return rbtree_case_5(node);
}

static leaf_t *rbtree_case_5(leaf_t *node)
{
    leaf_t *grandpa = rbtree_grandfather(node);

    node->parent->color = BLACK_NODE;
    grandpa->color = RED_NODE;

    if (node->parent->left == node) {
        rbtree_rotate_right(node->parent);
    } else {
        rbtree_rotate_left(node->parent);
    }

    return node->parent;
}

static void rbtree_rotate_left(leaf_t *node)
{
    leaf_t *g = node->parent;
    leaf_t *l = node->left;

    node->parent = g->parent;
    if (g->parent != NULL) {
        g->parent->right = node;
    }

    node->left = g;
    g->right = l;
    g->parent = node;
}

static void rbtree_rotate_right(leaf_t *node)
{
    leaf_t *g = node->parent;
    leaf_t *l = node->right;

    node->parent = g->parent;
    if (g->parent != NULL) {
        g->parent->left = node;
    }

    node->right = g;
    g->left = l;
    g->parent = node;
}

static void rbtree_put_node(leaf_t *root, leaf_t *node)
{
    if (node->value < root->value) {
        if (root->left != NULL) {
            rbtree_put_node(root->left, node);
        } else {
            root->left = node;
            node->parent = root;
        }
    } else {
        if (root->right != NULL) {
            rbtree_put_node(root->right, node);
        } else {
            root->right = node;
            node->parent = root;
        }
    }
}

leaf_t *rbtree_create_node(int value)
{
    leaf_t *node = (leaf_t *)malloc(sizeof(leaf_t));

    node->value = value;

    node->color = RED_NODE;

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}
