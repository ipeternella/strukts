#include <string.h>

#include "gtest/gtest.h"
#include "strukts_bstree.h"

#define str(s) ((char*)s)

namespace
{
    TEST(STRUKTS_BSTREE_SUITE, SHOULD_CREATE_EMPTY_BINARY_SEARCH_TREE)
    {
        /* act */
        StruktsBSTree* tree = strukts_bstree_new();

        /* assert */
        EXPECT_EQ(tree->size, 0);
        EXPECT_EQ(tree->root, nullptr);
        EXPECT_EQ(strukts_bstree_height(tree->root), -1); /* tree without nodes (no root node) */

        strukts_bstree_free(tree);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_CREATE_INSERT_ITEMS_ON_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        /* act */
        strukts_bstree_insert(tree, 12, str("12"));
        strukts_bstree_insert(tree, 5, str("5"));
        strukts_bstree_insert(tree, 18, str("18"));
        strukts_bstree_insert(tree, 15, str("15"));

        /* assert */;
        EXPECT_EQ(tree->size, 4);
        EXPECT_EQ(tree->root->key, 12);
        EXPECT_EQ(tree->root->left->key, 5);
        EXPECT_EQ(tree->root->right->key, 18);
        EXPECT_EQ(tree->root->right->left->key, 15);
        EXPECT_EQ(strukts_bstree_height(tree->root), 2);

        strukts_bstree_free(tree);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_GET_FIND_KEY_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        strukts_bstree_insert(tree, 12, str("12"));
        strukts_bstree_insert(tree, 5, str("5"));
        strukts_bstree_insert(tree, 18, str("18"));
        strukts_bstree_insert(tree, 15, str("15"));

        /* act */
        StruktsBSTNode* node = strukts_bstree_get(tree, 18);

        /* assert - current node */
        EXPECT_TRUE(node != nullptr);
        EXPECT_EQ(node->key, 18);
        EXPECT_TRUE(strcmp(node->value, str("18")) == 0);

        /* assert - adjacent node's children */
        EXPECT_EQ(node->left->key, 15);
        EXPECT_TRUE(node->right == nullptr);
        EXPECT_EQ(strukts_bstree_height(tree->root), 2);

        strukts_bstree_free(tree);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_DELETE_VALUES_FROM_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        strukts_bstree_insert(tree, 12, str("12"));
        strukts_bstree_insert(tree, 5, str("5"));
        strukts_bstree_insert(tree, 18, str("18"));
        strukts_bstree_insert(tree, 15, str("15"));
        strukts_bstree_insert(tree, 19, str("19"));
        strukts_bstree_insert(tree, 20, str("20"));

        /* act */
        bool success = strukts_bstree_delete(tree, 18);

        /* assert */
        EXPECT_TRUE(success);
        EXPECT_EQ(tree->size, 5);
        EXPECT_EQ(tree->root->key, 12);

        EXPECT_EQ(tree->root->right->key, 19);
        EXPECT_EQ(tree->root->left->key, 5);

        EXPECT_EQ(tree->root->right->left->key, 15);
        EXPECT_EQ(tree->root->right->right->key, 20);

        strukts_bstree_free(tree);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_DELETE_ROOT_NODE_FROM_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        strukts_bstree_insert(tree, 12, str("12"));
        strukts_bstree_insert(tree, 5, str("5"));
        strukts_bstree_insert(tree, 19, str("19"));
        strukts_bstree_insert(tree, 15, str("15")); /* expected successor */
        strukts_bstree_insert(tree, 20, str("20"));
        strukts_bstree_insert(tree, 16, str("16"));

        /* act */
        bool success = strukts_bstree_delete(tree, 12); /* deletes the root */

        /* assert */
        EXPECT_TRUE(success);
        EXPECT_EQ(tree->size, 5);
        EXPECT_EQ(tree->root->key, 15); /* successor */

        EXPECT_EQ(tree->root->right->key, 19);
        EXPECT_EQ(tree->root->left->key, 5);

        EXPECT_EQ(tree->root->right->left->key, 16);
        EXPECT_EQ(tree->root->right->right->key, 20);

        /* act */
        success = strukts_bstree_delete(tree, 5);

        /* assert */
        EXPECT_TRUE(success);
        EXPECT_EQ(tree->size, 4);
        EXPECT_EQ(tree->root->key, 15);
        EXPECT_TRUE(tree->root->left == nullptr);

        /* act */
        success = strukts_bstree_delete(tree, 20);

        EXPECT_TRUE(success);
        EXPECT_EQ(tree->size, 3);
        EXPECT_EQ(tree->root->key, 15);
        EXPECT_TRUE(tree->root->left == nullptr);

        EXPECT_EQ(tree->root->right->key, 19);
        EXPECT_TRUE(tree->root->left == nullptr);

        EXPECT_EQ(tree->root->right->right, nullptr);
        EXPECT_EQ(tree->root->right->left->key, 16);

        strukts_bstree_free(tree);
    }

    TEST(STRUKTS_BSTREE_SUITE, SHOULD_GET_MIN_AND_MAX_VALUES_IN_BINARY_SEARCH_TREE)
    {
        /* arrange */
        StruktsBSTree* tree = strukts_bstree_new();

        strukts_bstree_insert(tree, 12, str("12"));
        strukts_bstree_insert(tree, 5, str("5"));
        strukts_bstree_insert(tree, 9, str("9"));
        strukts_bstree_insert(tree, 2, str("2"));
        strukts_bstree_insert(tree, 18, str("18"));
        strukts_bstree_insert(tree, 15, str("15"));
        strukts_bstree_insert(tree, 17, str("17"));
        strukts_bstree_insert(tree, 9, str("9"));
        strukts_bstree_insert(tree, 16, str("16"));

        /* act */
        StruktsBSTNode* min_node = strukts_bstree_min(tree->root);
        StruktsBSTNode* max_node = strukts_bstree_max(tree->root);

        /* assert - metadata */
        EXPECT_EQ(tree->size, 9);

        /* assert - min and max */
        EXPECT_EQ(min_node->key, 2);
        EXPECT_EQ(max_node->key, 18);

        /* assert - tree height */
        EXPECT_EQ(strukts_bstree_height(tree->root), 4);

        strukts_bstree_free(tree);
    }
}  // namespace
