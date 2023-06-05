#pragma once
#include "..\lab2\BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& tree);
    ~BinarySearchTree() override = default;
    BinarySearchTree copySearchTree(const Node* node) const;
    using BinaryTree::getMinKey;
    using BinaryTree::getMaxKey;
    int getMinKey(const Node* node) const override;
    int getMaxKey(const Node* node) const override;
    using BinaryTree::addNode;
    Node* addNode(int key, Node* node, int priority = 0) override;
    using BinaryTree::deleteNode;
    void deleteNode(Node* nodeToDelete, Node* node) override;
    const Node* find(int key) const override;
    const Node* find(int key, const Node* node) const override;
    using BinaryTree::getLevelIndex;
    int getLevelIndex(int key, const Node* node) const override;

    BinarySearchTree& operator =(const BinarySearchTree& tree);
};
