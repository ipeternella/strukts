#include "gtest/gtest.h"
#include "strukts_bstree.h"

namespace
{
    TEST(STRUKTS_BSTREE_SUITE, SHOULD_CREATE_EMPTY_BINARY_SEARCH_TREE)
    {
        /* act */
        StruktsBSTree* tree = strukts_bstree_new();

        /* assert */
        EXPECT_EQ(tree->height, 0);
        EXPECT_EQ(tree->size, 0);
        EXPECT_EQ(tree->root, nullptr);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_CREATE_INSERT_ITEMS_ON_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        /* act */
        strukts_bstree_insert(tree, 12, (char*)"12");
        strukts_bstree_insert(tree, 5, (char*)"5");
        strukts_bstree_insert(tree, 18, (char*)"18");
        strukts_bstree_insert(tree, 15, (char*)"15");

        /* assert */;
        EXPECT_EQ(tree->size, 4);
        EXPECT_EQ(tree->height, 2);
        EXPECT_EQ(tree->root->key, 12);
        EXPECT_EQ(tree->root->left->key, 5);
        EXPECT_EQ(tree->root->right->key, 18);
        EXPECT_EQ(tree->root->right->left->key, 15);
    }
}  // namespace
