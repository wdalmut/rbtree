#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdint.h>

#define RED_NODE   2
#define BLACK_NODE 1

typedef uint8_t type_t;

struct leaf {
    int value;

    type_t color;

    struct leaf *parent;
    struct leaf *left;
    struct leaf *right;
};
typedef struct leaf leaf_t;

leaf_t *rbtree_create_node(int);
leaf_t *rbtree_put(leaf_t *, int);

#endif
