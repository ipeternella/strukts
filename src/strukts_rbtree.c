#include "strukts_rbtree.h"

#include <stdbool.h>
#include <stdlib.h>

/********************** PRIVATE FUNCTIONS **********************/
static inline StruktsRBTNode* strukts_rbtree_nil_node_new()
{
    StruktsRBTNode* nil_node = (StruktsRBTNode*)malloc(sizeof(StruktsRBTNode));

    if (nil_node == NULL)
        return NULL;

    nil_node->color = Black;
    nil_node->key = 0;
    nil_node->parent = NULL;
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->value = NULL;

    return nil_node;
}

/********************** PUBLIC FUNCTIONS **********************/
static void strukts_rbtree_left_rotate(StruktsRBTree* tree, StruktsRBTNode* node)
{
    StruktsRBTNode* pivot_node = node->right; /* the node in which the rotation will occur around */

    /* cannot left rotate the node around a nil node */
    if (pivot_node == tree->nil_node)
        return;

    /* adjust the right subtree of the node */
    node->right = pivot_node->left;

    if (pivot_node->left != tree->nil_node) {
        pivot_node->left->parent = node;
    }

    /* adjust the parent of the pivot node */
    if (node->parent == tree->nil_node)
        tree->root = pivot_node;
    else if (node == node->parent.left)
        node->parent->left = pivot_node;
    else
        node->parent->right = pivot_node;

    /* adjust the node to become a child of the pivot node to complete the left rotation */
    pivot_node->left = node;
    node->parent = pivot_node;
}

static void strukts_rbtree_right_rotate(StruktsRBTree* tree, StruktsRBTNode* node)
{
}

StruktsRBTNode* strukts_rbtree_new()
{
    StruktsRBTree* tree = (StruktsRBTree*)malloc(sizeof(StruktsRBTree));

    if (tree == NULL)
        return NULL;

    StruktsRBTNode* nil_node = strukts_rbtree_nil_node_new();

    if (nil_node == NULL) {
        free(tree);
        return NULL;
    }

    tree->root = nil_node;
    tree->nil_node = nil_node;

    return tree;
}