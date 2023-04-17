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
    Node* it = node, *new_node = new Node(key);
    while (true) {
        if (key < it->getKey()) {
            if (it->getLeft() == nullptr) {
                Node::setLeftConnection(it, new_node);
                return new_node;
            }
            it = it->getLeft();
        }
        else {
            if (it->getRight() == nullptr) {
                Node::setRightConnection(it, new_node);
                return new_node;
            }
            it = it->getRight();
        }
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

BinaryTree::Node *BinarySearchTree::find(int key, const BinaryTree::Node *node)
{
    return const_cast<BinaryTree::Node*>(const_cast<const BinarySearchTree*>(this)->find(key, node));
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

int BinarySearchTree::getMinKey() const
{
    return getMinKey(this->getRoot());
}

int BinarySearchTree::getMaxKey() const
{
    return getMaxKey(this->getRoot());
}

BinaryTree::Node *BinarySearchTree::addNode(int key, int priority)
{
    if (m_root == nullptr)
        return m_root = new Node(key);
    else
        return this->addNode(key, this->getRoot(), priority);
}

const BinaryTree::Node *BinarySearchTree::find(int key) const
{
    return this->find(key, this->getRoot());
}

BinaryTree::Node *BinarySearchTree::find(int key)
{
    return this->find(key, this->getRoot());
}

bool BinarySearchTree::deleteNode(int key)
{
    return this->deleteNode(key, this->getRoot());
}

bool BinarySearchTree::deleteNode(int key, BinaryTree::Node *node)
{
    Node* nodeToDelete = this->find(key, node);
    if (nodeToDelete == nullptr)
        return false;
    this->deleteNode(nodeToDelete, node);
    return true;
}

int BinarySearchTree::getLevelIndex(int key) const
{
    return this->getLevelIndex(key, this->getRoot());
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
