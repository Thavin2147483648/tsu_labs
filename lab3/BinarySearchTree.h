#pragma once
#include "..\lab2\BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& tree);
    ~BinarySearchTree() = default;
    BinarySearchTree copySearchTree(const Node* node) const;
    int getMinKey() const override;
    int getMaxKey() const override;
    int getMinKey(const Node* node) const override;
    int getMaxKey(const Node* node) const override;
    Node* addNode(int key, int priority = 0) override;
    Node* addNode(int key, Node* node, int priority = 0) override;
    bool deleteNode(int key) override;
    bool deleteNode(int key, Node* node) override;
    void deleteNode(Node* nodeToDelete, Node* node) override;
    virtual Node* find(int key) override;
    virtual const Node* find(int key) const override;
    Node* find(int key, const Node* node) override;
    const Node* find(int key, const Node* node) const override;
    int getLevelIndex(int key) const override;
    int getLevelIndex(int key, const Node* node) const override;

    BinarySearchTree& operator =(const BinarySearchTree& tree);
};
