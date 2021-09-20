/**
 * @file strukts_rbtree.h
 *
 * @brief Module that contains red black trees implementations.
 *
 * Red black trees are a way of having balanced trees to avoid worst case scenarios that
 * may happen with binary search trees.
 */

#ifndef STRUKTS_RBTREE_H
#define STRUKTS_RBTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

typedef enum { Red, Black } StruktsNodeColor;

/*
 * Represents a node in a red black tree with a key and its value (satellite data).
 */
typedef struct _StruktsRBTNode StruktsRBTNode;

struct _StruktsRBTNode {
    StruktsRBTNode* parent;
    StruktsRBTNode* left;
    StruktsRBTNode* right;
    StruktsNodeColor color; /* red or black */

    /* each object's id */
    int key;

    /* satellite data */
    char* value;
};

/*
 * Represents a red black tree structure which holds a reference to the root of the tree.
 */
typedef struct _StruktsRBTree StruktsRBTree;

struct _StruktsRBTree {
    StruktsRBTNode* root;
    StruktsRBTNode* nil_node; /* the NIL node used by the rbtree */
};

/**
 * Allocates a new empty red black tree structure.
 *
 * @return a pointer to an empty red black tree.
 */
StruktsRBTNode* strukts_rbtree_new();

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_RBTREE_H */