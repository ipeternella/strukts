#include "strukts_rbtree.h"

#include <stdbool.h>
#include <stdlib.h>

/********************** MACROS **********************/
#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

/********************** PRIVATE FUNCTIONS **********************/
static inline StruktsRBTNode* rbtree_nil_node_new()
{
    StruktsRBTNode* nil_node = (StruktsRBTNode*)malloc(sizeof(StruktsRBTNode));

    if (nil_node == NULL)
        return NULL;

    nil_node->color = Black; /* nil nodes are black */
    nil_node->key = 0;
    nil_node->parent = NULL;
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->value = NULL;

    return nil_node;
}

static inline StruktsRBTNode* rbtree_node_new(StruktsRBTree* tree, int key, char* value)
{
    StruktsRBTNode* new_node = (StruktsRBTNode*)malloc(sizeof(StruktsRBTNode));

    if (new_node == NULL)
        return NULL;

    new_node->color = Red; /* new nodes are red to have two black children and keep black height */
    new_node->key = key;
    new_node->value = value;
    new_node->parent = tree->nil_node;
    new_node->left = tree->nil_node;
    new_node->right = tree->nil_node;

    return new_node;
}

static inline bool is_left_child(StruktsRBTNode* node)
{
    return node == node->parent->left;
}

static inline bool is_right_child(StruktsRBTNode* node)
{
    return node == node->parent->right;
}

static inline bool is_tree_root(StruktsRBTree* tree, StruktsRBTNode* node)
{
    return node == tree->root;
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
    else if (node == node->parent->left)
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

static void rbtree_insert_fix(StruktsRBTree* tree, StruktsRBTNode* node)
{
    /*
     * New nodes are red so while its parent is also red we violate the r.b.tree
     * property which says that a red parent must have two black children.
     */
    while (node->parent->color == Red) {
        /* new node's parent is a left child */
        if (is_left_child(node->parent)) {
            /* right uncle is red */
            if (node->parent->parent->right->color == Red) {
                /* fixes tree up to its grand parent */
                node->parent->color = Black;                /* parent */
                node->parent->parent->right->color = Black; /* right uncle */
                node->parent->parent->color = Red;          /* grand parent */

                /* fixes the tree up to the node's grand parent and then loop again */
                node = node->parent->parent;
            }
            /* right uncle is black */
            else {
                /* if the uncle is black, for final right rotate, the node must be a LEFT child */
                if (is_right_child(node)) {
                    /* move the node up for left rotation */
                    node = node->parent;
                    rbtree_left_rotate(tree, node); /* makes the node become a left child */
                }
                node->parent->color = Black; /* parent becomes black, which finishes the loop */
                node->parent->parent->color = Red; /* grand parent */
                rbtree_right_rotate(tree,
                                    node->parent->parent); /* black parent goes one level up */
            }
        }
        /* mirrors the algorithm above: new node's parent is a right child */
        else {
            /* left uncle is red */
            if (node->parent->parent->left->color == Red) {
                node->parent->color = Black;
                node->parent->parent->left->color = Black;
                node->parent->parent->color = Red;

                /* fixes the tree up to the node's grandparent and then loop again */
                node = node->parent->parent;
            }
            /* left uncle is black */
            else {
                /* if the uncle is black, for final left rotate, the node must be a RIGHT child */
                if (is_left_child(node)) {
                    /* move the node up for right rotation */
                    node = node->parent;
                    rbtree_right_rotate(tree, node); /* makes the node become a right child */
                }
                node->parent->color = Black; /* parent becomes black, which finishes the loop */
                node->parent->parent->color = Red;
                rbtree_left_rotate(tree, node->parent->parent); /* black parent goes one level up */
            }
        }
    }

    /* the root and nil nodes (tree->nil) must be black in a r.b.tree */
    tree->root->color = Black;
}

/**
 * Replaces an old node with a new one and ajusts the new node's parent to point
 * to the old target's parent and make the old target's parent point (left or right)
 * to this new node. This operation is also known as a 'transplant'. Also, new_node
 * can be tree->nil.
 *
 * Notice: this method does NOT free the memory of the old_node or adjusts the new
 * node's left and right subtrees. These tasks are responsibilities of the caller.
 */
static void rbtree_node_replace(StruktsRBTree* tree, StruktsRBTNode* old_node,
                                StruktsRBTNode* new_node)
{
    if (is_tree_root(old_node)) {
        tree->root = new_node;
    } else if (is_left_child(old_node)) {
        old_node->parent.left = new_node;
    } else {
        old_node->parent->right = new_node;
    }

    /* no NULL check unlike in b.s.trees */
    new_node->parent = old_node->parent;
}

static void rbtree_delete_fix(StruktsRBTree* tree, StruktsRBTNode* node)
{
}

/********************** PUBLIC FUNCTIONS **********************/
StruktsRBTree* strukts_rbtree_new()
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

int strukts_rbtree_height(StruktsRBTree* tree, StruktsRBTNode* root)
{
    if (tree == NULL || root == NULL || root == tree->nil_node)
        return -1;

    return max(strukts_rbtree_height(tree, root->left), strukts_rbtree_height(tree, root->right)) +
           1;
}

bool strukts_rbtree_insert(StruktsRBTree* tree, int key, char* value)
{
    /* creates a red node with tree->nil_node left and right children */
    StruktsRBTNode* new_node = rbtree_node_new(tree, key, value);

    if (new_node == NULL)
        return false; /* allocation error */

    StruktsRBTNode* next = tree->root; /* start looking at the root of the tree */
    StruktsRBTNode* parent = tree->nil_node;

    /* parent will hold the new node's parent */
    while (next != tree->nil_node) {
        parent = next;

        if (key < next->key)
            next = next->left;
        else
            next = next->right;
    }

    /* sets new node's parent */
    new_node->parent = parent;

    /* sets parent reference */
    if (parent == tree->nil_node)
        tree->root = new_node;
    else if (key < parent->key)
        parent->left = new_node;
    else
        parent->right = new_node;

    /* as we might have a red child whose parent is also red, we need to fix the r.b.tree */
    rbtree_insert_fix(tree, new_node);

    return true;
}

StruktsRBTNode* strukts_rbtree_min(StruktsRBTree* tree, StruktsRBTNode* root)
{
    StruktsRBTNode* current_node = root;

    while (current_node->left != tree->nil_node) {
        current_node = current_node->left;
    }

    return current_node;
}

StruktsRBTNode* strukts_rbtree_max(StruktsRBTree* tree, StruktsRBTNode* root)
{
    StruktsRBTNode* current_node = root;

    while (current_node->right != tree->nil_node) {
        current_node = current_node->right;
    }

    return current_node;
}

StruktsRBTNode* strukts_rbtree_get(StruktsRBTree* tree, int key)
{
    StruktsRBTNode* current_node = tree->root;

    /* search for the key within the r.b.tree like in a b.s.tree */
    while (current_node != tree->nil_node) {
        if (key == current_node->key) /* found it */
            return current_node;
        else if (key > current_node->key)
            current_node = current_node->right;
        else
            current_node = current_node->left;
    }

    return current_node; /* might return tree->nil */
}

bool strukts_rbtree_delete(StruktsRBTree* tree, int key)
{
    /* grabs node with the key for deletion: the original target node */
    StruktsRBTNode* original_target = strukts_rbtree_get(tree, key);

    /* key does not exist in the tree */
    if (node_for_delete = tree->nil_node)
        return false;

    StruktsRBTNode* successor;
    StruktsRBTNode* target = original_target; /* begins as the original target */
    StruktsNodeColor removed_color = target->color;

    /* trivial cases: original target has just ONE child */
    if (target->left == tree->nil_node) {
        successor = target->right;
        rbtree_node_replace(tree, target, successor);
    } else if (target->right == tree->nil_node) {
        successor = target->left;
        rbtree_node_replace(tree, target, successor);
    }
    /* non-trivial case: original target has BOTH children */
    else {
        /* new target, removed color and successor */
        target = strukts_rbtree_min(tree, target->right);
        removed_color = target->color;
        successor = target->right; /* target is min node: has no left child */

        if (target->parent == original_target) {
            successor->parent = target; /* tree->nil may point to target */
        } else {
            rbtree_node_replace(tree, target, successor);
            target->right = original_target->right;
            target->right->parent = target;
        }

        /* finally replace target with the original target with the SAME original color */
        rbtree_node_replace(tree, original_target, target);
        target->left = original_target->left;
        target->left->parent = target;
        target->color = original_target->color; /* !: same orginal color :! */
    }

    if (removed_color == Black) {
        /* fix the r.b.tree as a black node was removed */
    }

    return true;
}