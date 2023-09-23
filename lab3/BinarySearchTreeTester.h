#pragma once
#include "..\lab2\BinaryTreeTester.h"

class BinarySearchTreeTester : public BinaryTreeTester
{
public:
    BinarySearchTreeTester() = default;
    ~BinarySearchTreeTester() override = default;
    void test(int size) override;
protected:
    bool isSearchTree(const BinaryTree& tree);
    bool isSearchTree(const BinaryTree::Node *root);
    int getMinKey(const BinaryTree::Node *node);
    int getMaxKey(const BinaryTree::Node *node);
    BinaryTree* allocateTree() override;
    void check_addAndCount(const BinaryTree& tree, int size) override;
    void check_remove(const BinaryTree& tree, int size) override;
    void check_clear(const BinaryTree& tree, int size) override;
    void check_assign(const BinaryTree::Node* tree1, const BinaryTree::Node* tree2) override;
};
