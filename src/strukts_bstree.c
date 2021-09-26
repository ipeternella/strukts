#include "strukts_bstree.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#include "sfmalloc.h"
#define malloc sf_malloc
#define free sf_free
#endif

/********************** MACROS **********************/
#define max(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

/********************** PRIVATE FUNCTIONS **********************/
static StruktsBSTNode* strukts_bstree_node_new(int key, char* value)
{
    StruktsBSTNode* node = (StruktsBSTNode*)malloc(sizeof(StruktsBSTNode));

    if (node == NULL)
        return NULL;

    /* references */
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    /* key */
    node->key = key;
    node->value = value;

    return node;
}

static void strukts_bstree_node_free(StruktsBSTNode* node)
{
    /* trivial case */
    if (node == NULL)
        return;

    /* store reference as parent will be freed so node->right can't be used */
    StruktsBSTNode* right = node->right;

    /* walks the tree deallocating nodes */
    strukts_bstree_node_free(node->left);
    free(node);
    strukts_bstree_node_free(right);
}

/*
 * Replaces an old node with a new one and ajusts the new node's parent to point
 * to the old target's parent and make the old target's parent point (left or right)
 * to this new node. This operation is also known as a 'transplant'. Also, new_node
 * can be NULL.
 *
 * Notice: this method does NOT free the memory of the old_node or adjusts the new
 * node's left and right subtrees. These tasks are responsibilities of the caller.
 */
static void strukts_bstree_node_replace(StruktsBSTree* tree, StruktsBSTNode* old_node,
                                        StruktsBSTNode* new_node)
{
    /*
     * Step 1: make the parent point to the new node. Checks if the old_node
     * is the root of the tree or if it's the left or right child of its parent.
     */
    if (old_node->parent == NULL)
        /* old_node was the root */
        tree->root = new_node;
    else if (old_node->parent->right == old_node)
        /* old_node was a right child */
        old_node->parent->right = new_node;
    else
        /* old_node was a left child */
        old_node->parent->left = new_node;

    /* Step 2: make the new_node refer back to its new parent */
    if (new_node != NULL)
        new_node->parent = old_node->parent;
}

/********************** PUBLIC FUNCTIONS **********************/
void strukts_bstree_walk_inorder(StruktsBSTNode* root)
{
    if (root == NULL)
        return;

    /* in-order walk: root in the middle */
    strukts_bstree_walk_inorder(root->left);
    printf("%d\n", root->key);
    strukts_bstree_walk_inorder(root->right);
}

StruktsBSTree* strukts_bstree_new()
{
    StruktsBSTree* tree = (StruktsBSTree*)malloc(sizeof(StruktsBSTree));

    if (tree == NULL)
        return NULL;

    tree->root = NULL;
    tree->size = 0;

    return tree;
}

bool strukts_bstree_insert(StruktsBSTree* tree, int key, char* value)
{
    StruktsBSTNode* new_node = strukts_bstree_node_new(key, value);

    /* allocation error */
    if (new_node == NULL)
        return false;

    StruktsBSTNode* current_node = tree->root;
    StruktsBSTNode* parent = NULL;

    /* walks the tree to find the parent position */
    while (current_node != NULL) {
        parent = current_node; /* last seen parent */

        if (new_node->key < current_node->key)
            current_node = current_node->left;
        else
            current_node = current_node->right;
    }

    /* update new node references */
    new_node->parent = parent;

    /* update parent references */
    if (parent == NULL)
        tree->root = new_node;
    else if (new_node->key < parent->key)
        parent->left = new_node;
    else
        parent->right = new_node;

    /* final tree metadata updating */
    tree->size++;

    return true;
}

/*
 * There are 3 cases which deletion must cover:
 *
 * 1. Trivial case: target node has no left subtree, just replace with right node
 * 2. Trivial case: target node has no right subtree, just replace with left node
 * 3. Target node has both children, so to find its successor we can either pick the
 *    max value of its left subtree or the min value of its right subtree as these can
 *    safely replace the target node and still respect the main property of a binary
 *    search tree. Here, we pick the min node of the right subtree of the target node to
 *    be the successor. Notice that this node will never have any left child (min node).
 *    After picking this successor, we check whether it's a direct right child of the
 *    target node.
 */
bool strukts_bstree_delete(StruktsBSTree* tree, int key)
{
    StruktsBSTNode* target_node = strukts_bstree_get(tree, key);

    /* if key does not exist, then no deletion */
    if (target_node == NULL)
        return false;

    if (target_node->left == NULL) {
        strukts_bstree_node_replace(tree, target_node, target_node->right);
    } else if (target_node->right == NULL) {
        strukts_bstree_node_replace(tree, target_node, target_node->left);
    } else {
        /* successor: min of the target_node->right subtree */
        StruktsBSTNode* successor = strukts_bstree_min(target_node->right);

        if (successor->parent != target_node) {
            /* successor has NO left node (it's a min), trivial swap to remove it from the tree */
            strukts_bstree_node_replace(tree, successor, successor->right);

            /* safe: target_node->right != successor, so successor can refer target_node->right */
            successor->right = target_node->right;
            successor->right->parent = successor;
        }

        /* successor takes target_node's left node and ajusts its parent */
        successor->left = target_node->left;
        successor->left->parent = successor;

        /* finally replace the successor with the target_node as left/right links are correct */
        strukts_bstree_node_replace(tree, target_node, successor);
    }

    /* frees allocated memory and metadata updating */
    free(target_node);
    tree->size--;

    return true;
}

StruktsBSTNode* strukts_bstree_min(StruktsBSTNode* root)
{
    StruktsBSTNode* current_node = root;

    while (current_node->left != NULL) {
        current_node = current_node->left;
    }

    return current_node;
}

StruktsBSTNode* strukts_bstree_max(StruktsBSTNode* root)
{
    StruktsBSTNode* current_node = root;

    while (current_node->right != NULL) {
        current_node = current_node->right;
    }

    return current_node;
}

StruktsBSTNode* strukts_bstree_get(StruktsBSTree* tree, int key)
{
    StruktsBSTNode* current_node = tree->root;

    /* search for the key within the bstree */
    while (current_node != NULL) {
        if (key == current_node->key) /* found it */
            return current_node;
        else if (key > current_node->key)
            current_node = current_node->right;
        else
            current_node = current_node->left;
    }

    return NULL;
}

int strukts_bstree_height(StruktsBSTNode* root)
{
    if (root == NULL)
        return -1;

    return max(strukts_bstree_height(root->left), strukts_bstree_height(root->right)) + 1;
}

void strukts_bstree_free(StruktsBSTree* tree)
{
    strukts_bstree_node_free(tree->root);

    free(tree);
}