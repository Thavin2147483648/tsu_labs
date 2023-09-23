#include <cassert>
#include "BinarySearchTreeTester.h"
#include "BinarySearchTree.h"

void BinarySearchTreeTester::test(int size)
{
    m_maxSize = size;
    generateNumbers();
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
}

BinaryTree *BinarySearchTreeTester::allocateTree()
{
    return new BinarySearchTree;
}

bool BinarySearchTreeTester::isSearchTree(const BinaryTree& tree)
{
    return isSearchTree(tree.getRoot());
}

bool BinarySearchTreeTester::isSearchTree(const BinaryTree::Node *root)
{
    if (root == nullptr)
        return true;
    if (root->getLeft() != nullptr && getMaxKey(root->getLeft()) > root->getKey())
        return false;
    if (root->getRight() != nullptr && getMinKey(root->getRight()) < root->getKey())
        return false;
    return isSearchTree(root->getLeft()) && isSearchTree(root->getRight());
}

void BinarySearchTreeTester::check_clear(const BinaryTree &tree, int size)
{
    BinaryTreeTester::check_clear(tree, size);
    assert(isSearchTree(tree));
}

void BinarySearchTreeTester::check_addAndCount(const BinaryTree &tree, int size)
{
    BinaryTreeTester::check_addAndCount(tree, size);
    assert(isSearchTree(tree));
}

void BinarySearchTreeTester::check_remove(const BinaryTree &tree, int size)
{
    BinaryTreeTester::check_remove(tree, size);
    assert(isSearchTree(tree));
}

void BinarySearchTreeTester::check_assign(const BinaryTree::Node *tree1, const BinaryTree::Node *tree2)
{
    BinaryTreeTester::check_assign(tree1, tree2);
    assert(isSearchTree(tree1));
    assert(isSearchTree(tree2));
}

int BinarySearchTreeTester::getMinKey(const BinaryTree::Node *node)
{
    if (node == nullptr)
        return INT_MAX;
    return std::min(std::min(getMinKey(node->getLeft()), getMinKey(node->getRight())), node->getKey());
}

int BinarySearchTreeTester::getMaxKey(const BinaryTree::Node *node)
{
    if (node == nullptr)
        return INT_MIN;
    return std::max(std::max(getMaxKey(node->getLeft()), getMaxKey(node->getRight())), node->getKey());
}
