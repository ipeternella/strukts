#include <string.h>

#include "gtest/gtest.h"
#include "strukts_rbtree.h"

#define str(s) ((char*)s)

namespace
{
    /**
     * r.b.tree-1 for testing:
     *
     *               _ 07 _
     *             /        \
     *           02'         11'
     *         /    \       /   \
     *       01      05    08    14
     *      /  \    /  \  /  \  /  \
     *     n   n   04' n n   n n   15'
     *
     *  - tree height  = 3 (edge counting)
     *  - black height = 2 (nils are black)
     *
     *  1. red nodes are marked with ', like 04';
     *  2. nil nodes are omitted
     */
    StruktsRBTree* build_testing_rbtree_1()
    {
        StruktsRBTree* tree = strukts_rbtree_new();

        strukts_rbtree_insert(tree, 11, str("eleven"));
        strukts_rbtree_insert(tree, 2, str("two"));
        strukts_rbtree_insert(tree, 14, str("fourteen"));
        strukts_rbtree_insert(tree, 15, str("fifteen"));
        strukts_rbtree_insert(tree, 7, str("seven"));
        strukts_rbtree_insert(tree, 1, str("one"));
        strukts_rbtree_insert(tree, 5, str("five"));
        strukts_rbtree_insert(tree, 8, str("eight"));
        strukts_rbtree_insert(tree, 4, str("four"));

        return tree;
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_CREATE_EMPTY_RED_BLACK_TREE)
    {
        /* act */
        StruktsRBTree* tree = strukts_rbtree_new();

        /* assert */
        EXPECT_EQ(tree->root, tree->nil_node);
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), -1); /* empty tree */
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_INSERT_NODES_INTO_RED_BLACK_TREE)
    {
        /* arrange */
        StruktsRBTree* tree = strukts_rbtree_new();

        /* act (builds r.b.tree-1 for testing */
        strukts_rbtree_insert(tree, 11, str("eleven"));
        strukts_rbtree_insert(tree, 2, str("two"));
        strukts_rbtree_insert(tree, 14, str("fourteen"));
        strukts_rbtree_insert(tree, 15, str("fifteen"));
        strukts_rbtree_insert(tree, 7, str("seven"));
        strukts_rbtree_insert(tree, 1, str("one"));
        strukts_rbtree_insert(tree, 5, str("five"));
        strukts_rbtree_insert(tree, 8, str("eight"));

        /* assert */
        EXPECT_EQ(tree->root->key, 11);
        EXPECT_EQ(tree->root->color, Black);
        EXPECT_EQ(tree->root->left->right->left->key, 5);
        EXPECT_EQ(tree->root->left->right->left->color, Red);
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), 3);

        /* act - should trigger a fix up as node 5 is red and 4 would be a red child too */
        strukts_rbtree_insert(tree, 4, str("four"));

        /* assert - node 7 will take the root due to right rotation */
        EXPECT_EQ(tree->root->key, 7);
        EXPECT_EQ(tree->root->color, Black);

        /* assert - balanced tree: height should not be 4, should remain 3 due to rotations */
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), 3);
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_DELETE_NODES_FROM_RED_BLACK_TREE)
    {
        /* arrange */
        StruktsRBTree* tree = build_testing_rbtree_1();

        /* act */
        strukts_rbtree_delete(tree, 7); /* deletes the root */

        /* assert */
        EXPECT_EQ(tree->root->key, 8);
        EXPECT_EQ(tree->root->color, Black); /* root must always be black */

        /* assert - 1 level below the root */
        EXPECT_EQ(tree->root->right->key, 14);
        EXPECT_EQ(tree->root->right->color, Red);
        EXPECT_EQ(tree->root->left->key, 2);
        EXPECT_EQ(tree->root->left->color, Red);

        /* assert - 2 levels below the root */
        EXPECT_EQ(tree->root->right->left->key, 11);
        EXPECT_EQ(tree->root->right->left->color, Black);
        EXPECT_EQ(tree->root->right->left->left, tree->nil_node);
        EXPECT_EQ(tree->root->right->left->right, tree->nil_node);
        EXPECT_EQ(tree->root->right->right->key, 15);
        EXPECT_EQ(tree->root->right->right->color, Black);
        EXPECT_EQ(tree->root->right->right->left, tree->nil_node);
        EXPECT_EQ(tree->root->right->right->right, tree->nil_node);

        EXPECT_EQ(tree->root->left->left->key, 1);
        EXPECT_EQ(tree->root->left->left->color, Black);
        EXPECT_EQ(tree->root->left->left->left, tree->nil_node);
        EXPECT_EQ(tree->root->left->left->right, tree->nil_node);
        EXPECT_EQ(tree->root->left->right->key, 5);
        EXPECT_EQ(tree->root->left->right->color, Black);
        EXPECT_EQ(tree->root->left->right->right, tree->nil_node);

        /* assert - 3 levels below the root */
        EXPECT_EQ(tree->root->left->right->left->key, 4);
        EXPECT_EQ(tree->root->left->right->left->color, Red);
        EXPECT_EQ(tree->root->left->right->left->right, tree->nil_node);
        EXPECT_EQ(tree->root->left->right->left->left, tree->nil_node);

        /* assert - nil node */
        EXPECT_EQ(tree->nil_node->color, Black);
    }
}  // namespace
