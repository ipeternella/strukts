#include <string.h>

#include "gtest/gtest.h"
#include "strukts_rbtree.h"

#define str(s) ((char*)s)

namespace
{
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

        /* act */
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
}  // namespace
