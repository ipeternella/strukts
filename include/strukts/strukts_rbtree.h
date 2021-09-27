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
StruktsRBTree* strukts_rbtree_new();

/**
 * Inserts a new node (red) on a red black tree. This function fixes up the
 * red black tree properties after the insertion.
 *
 * @param key is the key of the new node.
 * @param value is the value associated with the new node.
 *
 * @return true if the insertion was successful; otherwise, returns false in case
 * an allocation error happened.
 */
bool strukts_rbtree_insert(StruktsRBTree* tree, int key, char* value);

/**
 * Computes the height of the given red black tree. The notion of 'height' used here
 * is the based on edges count (connection between two nodes) and not on nodes count. Possible
 * scenarios:
 *
 * - if the tree contains a nil_node root, the height is -1;
 * - if the tree contains a single node (just the root), the height is 0;
 * - if the tree contains more than one node (root + others), the height is > 0.
 *
 * @param tree is the tree which contains a reference to the nil_node of the r.b.tree.
 * @param root_node is the root of the tree to start computing the height.
 *
 * @return the size of the tree based on edge counting (not node counting).
 */
int strukts_rbtree_height(StruktsRBTree* tree, StruktsRBTNode* root);

/**
 * Deletes a given key from the red black tree (if it exists).
 *
 * @param tree is the r.b.tree to delete the node from.
 * @param key is the key of the node to be deleted from the r.b.tree.
 *
 * @return true if the key was deleted; false if it was not found in the tree.
 */
bool strukts_rbtree_delete(StruktsRBTree* tree, int key);

/**
 * Returns the min value found in a red black tree.
 *
 * @param tree is a red black tree to look for its min value.
 *
 * @return pointer to the node with the min value of the tree. If the tree is empty,
 * returns r.b.tree's nil node.
 */
StruktsRBTNode* strukts_rbtree_min(StruktsRBTree* tree, StruktsRBTNode* root);

/**
 * Returns the max value found in a red black tree.
 *
 * @param tree is a red black tree to look for its max value.
 *
 * @return pointer to the node with the max value of the tree. If the tree is empty,
 * returns r.b.tree's nil node.
 */
StruktsRBTNode* strukts_rbtree_max(StruktsRBTree* tree, StruktsRBTNode* root);

/**
 * Deallocates all memory used by the red black tree and its nodes.
 */
void strukts_rbtree_free(StruktsRBTree* tree);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_RBTREE_H */