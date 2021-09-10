/**
 * @file strukts_hashing.h
 *
 * @brief Module that contains binary search trees.
 *
 * Search tree data structures can be used to implement dynamic sets operations (data queries and
 * data modifications). Binary search trees are a great starting point for more advanced tree
 * structures.
 */

#ifndef STRUKTS_BSTREE_H
#define STRUKTS_BSTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/*
 * Represents a node in a binary search tree with a key and its value (satellite data).
 */
typedef struct _StruktsBSTNode StruktsBSTNode;

struct _StruktsBSTNode {
    StruktsBSTNode* parent;
    StruktsBSTNode* left;
    StruktsBSTNode* right;

    /* each object's id */
    int key;

    /* satellite data */
    char* value;
};

/*
 * Represents a binary search tree structure which holds a reference to the root of the tree
 * along some useful metadata such as the current tree's height, size, etc.
 */
typedef struct _StruktsBSTree StruktsBSTree;

struct _StruktsBSTree {
    StruktsBSTNode* root;

    /* metadata */
    size_t size;
    size_t height;
};

/**
 * Prints to stdout all the keys in a binary search tree in order, that is, the left subtree
 * is print, then its root and finally the right subtree. Hence, the root of the tree is print
 * between the values of the left and right subtrees.
 *
 * @param root is the root of a binary search tree.
 */
void strukts_bstree_walk_inorder(StruktsBSTNode* root);

/**
 * Allocates a new empty binary search tree structure.
 *
 * @return a pointer to an empty binary search tree.
 */
StruktsBSTree* strukts_bstree_new();

/**
 * Inserts a new node into a binary search tree.
 *
 * @param tree is the BSTree to insert the new node at.
 * @param key is the key of the new node that will be added.
 * @param value is the value associated with a key that will be added.
 *
 * @return true if the insertion was successful (no allocation errors); otherwise, false.
 */
bool strukts_bstree_insert(StruktsBSTree* tree, int key, char* value);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_BSTREE_H */