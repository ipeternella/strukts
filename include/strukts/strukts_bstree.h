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
    size_t size; /* amount of nodes != height */
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
 * Computes the height of the given binary search tree. The notion of 'height' used here
 * is the based on edges count (connection between two nodes) and not on nodes count. Possible
 * scenarios:
 *
 * - if the tree contains a NULL root, the height is -1;
 * - if the tree contains a single node (just the root), the height is 0;
 * - if the tree contains more than one node (root + others), the height is > 0.
 *
 * @param root_node is the root of the tree to start computing the height.
 *
 * @return the size of the tree based on edge counting (not node counting).
 */
int strukts_bstree_height(StruktsBSTNode* root);

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

/**
 * Searches for a node with a given key within the binary search tree.
 *
 * @param tree is the BSTree to search for the keye
 * @param key is the key to search for in the BSTree
 *
 * @return a pointer to the node that contains the key if the key was found in the tree;
 * otherwise, returns NULL.
 */
StruktsBSTNode* strukts_bstree_get(StruktsBSTree* tree, int key);

/**
 * Deletes a node with a given key from the tree.
 *
 * @param tree is the tree to delete the node from.
 * @param key is the key of the node to be deleted from the tree.
 */
void strukts_bstree_delete(StruktsBSTree* tree, int key);

/**
 * Returns the min value found in a binary search tree.
 *
 * @param tree a binary search tree to look for its min value.
 *
 * @return pointer to the node with the min value of the tree. If the tree is empty,
 * returns NULL.
 */
StruktsBSTNode* strukts_bstree_min(StruktsBSTree* tree);

/**
 * Returns the max value found in a binary search tree.
 *
 * @param tree a binary search tree to look for its max value.
 *
 * @return pointer to the node with the max value of the tree. If the tree is empty,
 * returns NULL.
 */
StruktsBSTNode* strukts_bstree_max(StruktsBSTree* tree);

/**
 * Deallocates all memory used by the binary search tree and its nodes.
 *
 * @return true if the deallocation was successfull; false, otherwise.
 */
void strukts_bstree_free(StruktsBSTree* tree);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_BSTREE_H */