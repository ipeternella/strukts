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
#define IS_LEXICO_LESS(s1, s2) (strcmp(s1, s2) < 0 ? true : false) /* lexicographically less */

/********************** PRIVATE FUNCTIONS **********************/
static StruktsBSTNode* strukts_bstnode_new(int key, char* value)
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

static void strukts_bstnode_free(StruktsBSTNode* node)
{
    /* trivial case */
    if (node == NULL)
        return;

    /* store reference as parent will be freed so node->right can't be used */
    StruktsBSTNode* right = node->right;

    /* walks the tree deallocating nodes */
    strukts_bstnode_free(node->left);
    free(node);
    strukts_bstnode_free(right);
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
    tree->height = 0;

    return tree;
}

bool strukts_bstree_insert(StruktsBSTree* tree, int key, char* value)
{
    StruktsBSTNode* new_node = strukts_bstnode_new(key, value);

    /* allocation error */
    if (new_node == NULL)
        return false;

    StruktsBSTNode* current_node = tree->root;
    StruktsBSTNode* parent = NULL;
    size_t height = 0;

    /* walks the tree to find the parent position */
    while (current_node != NULL) {
        parent = current_node; /* last seen parent */

        if (new_node->key < current_node->key)
            current_node = current_node->left;
        else
            current_node = current_node->right;

        height++;
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
    tree->height = height;

    return true;
}

StruktsBSTNode* strukts_bstree_min(StruktsBSTree* tree)
{
    StruktsBSTNode* current_node = tree->root;

    while (current_node->left != NULL) {
        current_node = current_node->left;
    }

    return current_node;
}

StruktsBSTNode* strukts_bstree_max(StruktsBSTree* tree)
{
    StruktsBSTNode* current_node = tree->root;

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

void strukts_bstree_free(StruktsBSTree* tree)
{
    strukts_bstnode_free(tree->root);

    free(tree);
}