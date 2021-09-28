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
    static StruktsRBTree* build_testing_rbtree_1()
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

    static bool is_node_with_no_children(StruktsRBTree* tree, StruktsRBTNode* node)
    {
        return node->left == tree->nil_node && node->right == tree->nil_node;
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_CREATE_EMPTY_RED_BLACK_TREE)
    {
        /* act */
        StruktsRBTree* tree = strukts_rbtree_new();

        /* assert */
        EXPECT_EQ(tree->root, tree->nil_node);
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), -1); /* empty tree */

        strukts_rbtree_free(tree);
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

        strukts_rbtree_free(tree);
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_GET_NODE_FROM_RED_BLACK_TREE)
    {
        /* arrange */
        StruktsRBTree* tree = build_testing_rbtree_1();

        /* act */
        StruktsRBTNode* node = strukts_rbtree_get(tree, 8);

        /* assert - found key*/
        EXPECT_EQ(node->key, 8);

        /* act */
        node = strukts_rbtree_get(tree, 25);

        /* assert */
        EXPECT_EQ(node, tree->nil_node);

        strukts_rbtree_free(tree);
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

        strukts_rbtree_free(tree);
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_DELETE_MANY_NODES_FROM_RED_BLACK_TREE)
    {
        /* arrange */
        StruktsRBTree* tree = build_testing_rbtree_1();

        /* act */
        strukts_rbtree_delete(tree, 7); /* deletes the root */
        strukts_rbtree_delete(tree, 8); /* deletes the root */

        /* assert */
        EXPECT_EQ(tree->root->key, 11);
        EXPECT_EQ(tree->root->color, Black); /* root must always be black */

        EXPECT_EQ(tree->root->right->key, 14);
        EXPECT_EQ(tree->root->right->color, Black);
        EXPECT_EQ(tree->root->right->left, tree->nil_node);

        EXPECT_EQ(tree->root->right->right->key, 15);
        EXPECT_EQ(tree->root->right->right->color, Red);

        EXPECT_TRUE(is_node_with_no_children(tree, tree->root->right->right));

        /* act */
        strukts_rbtree_delete(tree, 11); /* deletes the root */

        /* assert */
        EXPECT_EQ(tree->root->key, 14);
        EXPECT_EQ(tree->root->color, Black);

        EXPECT_EQ(tree->root->right->key, 15);
        EXPECT_EQ(tree->root->right->color, Black);
        EXPECT_TRUE(is_node_with_no_children(tree, tree->root->right));
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), 3);

        EXPECT_EQ(tree->root->left->right->left->key, 4);
        EXPECT_EQ(tree->root->left->right->left->color, Red);
        EXPECT_TRUE(is_node_with_no_children(tree, tree->root->left->right->left));

        /* act */
        strukts_rbtree_delete(tree, 4); /* deletes non-root red node */

        /* assert */
        EXPECT_EQ(strukts_rbtree_height(tree, tree->root), 2);

        strukts_rbtree_free(tree);
    }

    TEST(STRUKTS_RBTREE_SUITE, SHOULD_ASSERT_MAX_MIN_OF_RED_BLACK_TREE)
    {
        /* arrange */
        StruktsRBTree* tree = build_testing_rbtree_1();

        /* act */
        StruktsRBTNode* max_node = strukts_rbtree_max(tree, tree->root);
        StruktsRBTNode* min_node = strukts_rbtree_min(tree, tree->root);

        /* assert */
        EXPECT_EQ(max_node->key, 15);
        EXPECT_EQ(max_node->color, Red);
        EXPECT_EQ(min_node->key, 1);
        EXPECT_EQ(min_node->color, Black);

        strukts_rbtree_free(tree);
    }
}  // namespace
