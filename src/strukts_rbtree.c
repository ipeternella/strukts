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

/*
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
    if (is_tree_root(tree, old_node)) {
        tree->root = new_node;
    } else if (is_left_child(old_node)) {
        old_node->parent->left = new_node;
    } else {
        old_node->parent->right = new_node;
    }

    /* no NULL check unlike in b.s.trees */
    new_node->parent = old_node->parent;
}

static void rbtree_delete_fix(StruktsRBTree* tree, StruktsRBTNode* node)
{
    StruktsRBTNode* right_sibling;
    StruktsRBTNode* left_sibling;

    while (node != tree->root && node->color == Black) {
        if (is_left_child(node)) {
            right_sibling = node->parent->right;

            /*
             * Case 1: sibling is RED -> just converts into case 2. In all other
             * cases the sibling is BLACK.
             */
            if (right_sibling->color == Red) {
                right_sibling->color = Black;
                node->parent->color = Red;
                rbtree_left_rotate(tree, node->parent);
                right_sibling = node->parent->right;
            }

            /*
             * Case 2: sibling's children are both BLACK. Remove black from right sibling
             * ('red' it) and move the node up to its parent which, if it's a red node,
             * ends the loop and becomes a black node in the end of this function.
             */
            if (right_sibling->left->color == Black && right_sibling->right->color == Black) {
                right_sibling->color = Red;
                node = node->parent; /* becomes black in the end, adding missing black node */
            } else {
                /*
                 * Case 3: sibling's left children is RED. Converts to case 4.
                 */
                if (right_sibling->right->color == Black) {
                    right_sibling->left->color = Black;
                    right_sibling->color = Red;
                    rbtree_right_rotate(tree, right_sibling);
                    right_sibling = node->parent->right;
                }

                /*
                 * Case 4: sibling's right children is RED. After the rotation, node's
                 * parent becomes a black node which adds the missing black node.
                 */
                right_sibling->color = node->parent->color;
                node->parent->color = Black; /* readds missing black node */
                right_sibling->right->color = Black;
                rbtree_left_rotate(tree, node->parent);
                node = tree->root; /* finishes the loop */
            }
        }
        /* node is a right child: symmetric from above */
        else {
            left_sibling = node->parent->left;

            /* case 1: sibling is RED, all other cases the sibling is BLACK */
            if (left_sibling->color == Red) {
                left_sibling->color = Black;
                node->parent->color = Red;
                rbtree_right_rotate(tree, node->parent);
                left_sibling = node->parent->left;
            }

            /* case 2 */
            if (left_sibling->right->color == Black && left_sibling->left->color == Black) {
                left_sibling->color = Red;
                node = node->parent; /* becomes black in the end, adding missing black node */
            } else {
                /* case 3 */
                if (left_sibling->left->color == Black) {
                    left_sibling->right->color = Black;
                    left_sibling->color = Red;
                    rbtree_left_rotate(tree, left_sibling);
                    left_sibling = node->parent->left;
                }

                /* case 4 */
                left_sibling->color = node->parent->color;
                node->parent->color = Black; /* readds missing black node */
                left_sibling->left->color = Black;
                rbtree_right_rotate(tree, node->parent);
                node = tree->root; /* finishes the loop */
            }
        }
    }

    node->color = Black;
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
    /* grabs node with the key for deletion: the target node */
    StruktsRBTNode* target = strukts_rbtree_get(tree, key);

    /* key does not exist in the tree */
    if (target == tree->nil_node)
        return false;

    StruktsRBTNode* successor;       /* holds a node that might succeed the target node */
    StruktsRBTNode* node_for_repair; /* holds a possibly unbalanced node to fix later */
    StruktsNodeColor lost_color;     /* color that the tree loses from deletion */

    /* in the trivial cases, the lost color belongs to the removed target node */
    lost_color = target->color;

    /*
     * Trivial cases: Here, the target node is removed and its color is the one
     * removed (lost) from the tree. Here, this removed color will be used to see if the
     * r.b.tree needs to be 'repaired' as a black color node might have been removed.
     */
    if (target->left == tree->nil_node) {
        node_for_repair = target->right; /* node for repair is the target's successor */
        rbtree_node_replace(tree, target, node_for_repair);
    } else if (target->right == tree->nil_node) {
        node_for_repair = target->left;
        rbtree_node_replace(tree, target, node_for_repair);
    } else {
        /*
         * Non-trivial case: the target node has BOTH children. In this case, the min node
         * of the target's right subtree becomes the target's successor in the tree and will
         * replace the target with the SAME color. As such, the r.b.tree color does not become
         * unbalanced in terms of colors at the target's position (same color is sustained),
         * however, as the min node is moved from its original position, this old position "loses"
         * its color and, if that color is BLACK, it unbalances the r.b.tree's color and must be
         * repaired in the end.
         */
        successor = strukts_rbtree_min(tree, target->right);
        lost_color = successor->color;      /* successor assumes target's color and loses its own */
        node_for_repair = successor->right; /* target is min node: has no left child */

        if (successor->parent == target) {
            node_for_repair->parent = successor; /* tree->nil may point to target */
        } else {
            rbtree_node_replace(tree, successor, node_for_repair); /* frees successor from tree */
            successor->right = target->right;
            successor->right->parent = successor;
        }

        /* finally replace the target with its successor with the same color */
        rbtree_node_replace(tree, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
        successor->color = target->color; /* same color so tree loses successor's color */
    }

    /* if the lost color was black, the r.b.tree must be fixed starting from the repair node */
    if (lost_color == Black)
        rbtree_delete_fix(tree, node_for_repair);

    return true;
}
