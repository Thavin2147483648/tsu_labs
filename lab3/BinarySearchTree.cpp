#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree() : BinaryTree()
{}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &tree) : BinaryTree(tree)
{}

BinarySearchTree BinarySearchTree::copySearchTree(const BinaryTree::Node *node) const
{
    BinarySearchTree tree;
    tree.m_root = this->m_copyTree(node);
    return tree;
}

int BinarySearchTree::getMinKey(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return INT_MAX;
    while (node->getLeft() != nullptr)
        node = node->getLeft();
    return node->getKey();
}

int BinarySearchTree::getMaxKey(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return INT_MIN;
    while (node->getRight() != nullptr)
        node = node->getRight();
    return node->getKey();
}

BinaryTree::Node *BinarySearchTree::addNode(int key, BinaryTree::Node *node, int priority)
{
    if (node == nullptr)
        return this->BinaryTree::addNode(key, priority);
    Node* it = node, *new_node;
    while (true) {
        if (key < it->getKey()) {
            if (it->getLeft() == nullptr) {
                new_node = new Node(key);
                Node::setLeftConnection(it, new_node);
                return new_node;
            }
            it = it->getLeft();
        }
        else if (key > it->getKey()) {
            if (it->getRight() == nullptr) {
                new_node = new Node(key);
                Node::setRightConnection(it, new_node);
                return new_node;
            }
            it = it->getRight();
        }
        else
            return it;
    }
}

void BinarySearchTree::deleteNode(BinaryTree::Node *nodeToDelete, BinaryTree::Node *node)
{
    if (nodeToDelete->getChildrenCount() == 0) {
        if (nodeToDelete == m_root) {
            delete nodeToDelete;
            m_root = nullptr;
            return;
        }
        Node* parent = nodeToDelete->getParent();
        if (parent->getLeft() == nodeToDelete)
            Node::setLeftConnection(parent, nullptr);
        else
            Node::setRightConnection(parent, nullptr);
        delete nodeToDelete;
        return;
    }
    Node* nodeReplacement = nodeToDelete;
    if (nodeReplacement->getLeft() == nullptr) {
        nodeReplacement = nodeReplacement->getRight();
        while (nodeReplacement->getLeft() != nullptr)
            nodeReplacement = nodeReplacement->getLeft();
    }
    else {
        nodeReplacement = nodeReplacement->getLeft();
        while (nodeReplacement->getRight() != nullptr)
            nodeReplacement = nodeReplacement->getRight();
    }
    nodeToDelete->setKey(nodeReplacement->getKey());
    this->deleteNode(nodeReplacement, node);
}

const BinaryTree::Node *BinarySearchTree::find(int key, const BinaryTree::Node *node) const
{
    const Node* it = node;
    while (it != nullptr && it->getKey() != key) {
        if (key < it->getKey())
            it = it->getLeft();
        else
            it = it->getRight();
    }
    return it;
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &tree)
{
    if (&tree == this)
        return *this;
    this->deleteTree();
    this->m_root = tree.m_copyTree(tree.m_root);
    return *this;
}

const BinaryTree::Node *BinarySearchTree::find(int key) const
{
    return this->find(key, this->getRoot());
}

int BinarySearchTree::getLevelIndex(int key, const BinaryTree::Node *node) const
{
    const Node* it = node;
    int index = 0;
    while (it != nullptr && it->getKey() != key) {
        if (key < it->getKey())
            it = it->getLeft();
        else
            it = it->getRight();
        ++index;
    }
    if (it == nullptr)
        return -1;
    return index;
}
