#include "strukts_rbtree.h"

#include <stdbool.h>
#include <stdlib.h>

/********************** PRIVATE FUNCTIONS **********************/
static inline StruktsRBTNode* rbtree_nil_node_new()
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

static inline bool is_left_child(StruktsRBTNode* node)
{
    return node == node->parent->left;
}

static inline bool is_right_child(StruktsRBTNode* node)
{
    return node == node->parent->right;
}

static void rbtree_left_rotate(StruktsRBTree* tree, StruktsRBTNode* node)
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
    pivot_node->parent = node->parent;

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

static void rbtree_right_rotate(StruktsRBTree* tree, StruktsRBTNode* node)
{
    StruktsRBTNode* pivot_node = node->left; /* the node in which the rotation will occur around */

    /* cannot left rotate the node around a nil node */
    if (pivot_node == tree->nil_node)
        return;

    /* adjusts left subtree of the node */
    node->left = pivot_node->right;

    if (pivot_node->right != tree->nil_node)
        pivot_node->right->parent = node;

    /* adjust the parent of the pivot node */
    pivot_node->parent = node->parent;

    if (node->parent == tree->nil_node)
        tree->root = pivot_node;
    else if (node == node->parent->left)
        node->parent->left = pivot_node;
    else
        node->parent->right = pivot_node;

    /* adjust the node to become a child of the pivot node to complete the right rotation */
    pivot_node->right = node;
    node->parent = pivot_node;
}

static void strukts_rbtree_insert_fix(StruktsRBTree* tree, StruktsRBTNode* node)
{
    StruktsRBTNode* right_uncle;
    StruktsRBTNode* left_uncle;
    StruktsRBTNode* grand_parent;
    StruktsRBTNode* parent;

    /*
     * New nodes are red so while its parent is also red we violate the r.b.tree
     * property which says that a red parent must have two black children.
     */
    while (node->parent->color == Red) {
        /* new node's parent is a left child */
        if (is_left_child(node->parent)) {
            right_uncle = node->parent->parent->right;
            grand_parent = node->parent->parent;
            parent = node->parent;

            /* right uncle is red */
            if (right_uncle->color == Red) {
                /* fixes tree up to its grande parent */
                parent->color = Black;
                right_uncle->color = Black;
                grand_parent->color = Red;

                /* fixes the tree up to the node's grandparent and then loop again */
                node = grand_parent;
            }
            /* right uncle is black */
            else {
                /* if the uncle is black, for final right rotate, the node must be a LEFT child */
                if (is_right_child(node)) {
                    node = parent;
                    rbtree_left_rotate(tree, node); /* makes the node become a left child */
                }
                parent->color = Black; /* parent becomes black, which finishes the loop */
                grand_parent->color = Red;
                rbtree_right_rotate(tree, grand_parent); /* black parent goes one level up */
            }
        } else {
            /* mirrors the algorithm above: new node's parent is a right child */
            left_uncle = node->parent->parent->left;
            grand_parent = node->parent->parent;
            parent = node->parent;

            if (left_uncle->color == Red) {
                parent->color = Black;
                left_uncle->color = Black;
                grand_parent->color = Red;

                /* fixes the tree up to the node's grandparent and then loop again */
                node = grand_parent;
            }
            /* left uncle is black */
            else {
                /* if the uncle is black, for final left rotate, the node must be a RIGHT child */
                if (is_left_child(node)) {
                    node = parent;
                    rbtree_right_rotate(tree, node); /* makes the node become a right child */
                }
                parent->color = Black; /* parent becomes black, which finishes the loop */
                grand_parent->color = Red;
                rbtree_left_rotate(tree, grand_parent); /* black parent goes one level up */
            }
        }
    }

    /* the root and nil nodes (tree->nil) must be black in a r.b.tree */
    tree->root->color = Black;
}

/********************** PUBLIC FUNCTIONS **********************/
StruktsRBTNode* strukts_rbtree_new()
{
    StruktsRBTree* tree = (StruktsRBTree*)malloc(sizeof(StruktsRBTree));

    if (tree == NULL)
        return NULL;

    StruktsRBTNode* nil_node = rbtree_nil_node_new();

    if (nil_node == NULL) {
        free(tree);
        return NULL;
    }

    tree->root = nil_node;
    tree->nil_node = nil_node;

    return tree;
}