#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>


BinaryTree::Node::Node(int key, Node *parent, Node *left, Node *right)
{
    m_parent = parent;
    m_left = left;
    m_right = right;
    m_key = key;
}

const BinaryTree::Node *BinaryTree::Node::getParent() const
{
    return m_parent;
}

const BinaryTree::Node *BinaryTree::Node::getLeft() const
{
    return m_left;
}

const BinaryTree::Node *BinaryTree::Node::getRight() const
{
    return m_right;
}

BinaryTree::Node *BinaryTree::Node::getParent()
{
    return m_parent;
}

BinaryTree::Node *BinaryTree::Node::getLeft()
{
    return m_left;
}

BinaryTree::Node *BinaryTree::Node::getRight()
{
    return m_right;
}

int BinaryTree::Node::getKey() const
{
    return m_key;
}

void BinaryTree::Node::m_setParent(Node *parent)
{
    m_parent = parent;
}

void BinaryTree::Node::m_setLeft(Node *left)
{
    m_left = left;
}

void BinaryTree::Node::m_setRight(Node *right)
{
    m_right = right;
}

void BinaryTree::Node::setKey(int key)
{
    m_key = key;
}

int BinaryTree::Node::getChildrenCount() const
{
    return (int)(m_left != nullptr) + (int)(m_right != nullptr);
}

void BinaryTree::Node::setLeftConnection(BinaryTree::Node *parent, BinaryTree::Node *left)
{
    if (parent != nullptr)
        parent->m_setLeft(left);
    if (left != nullptr)
        left->m_setParent(parent);
}

void BinaryTree::Node::setRightConnection(BinaryTree::Node *parent, BinaryTree::Node *right)
{
    if (parent != nullptr)
        parent->m_setRight(right);
    if (right != nullptr)
        right->m_setParent(parent);
}

bool BinaryTree::Node::isLeft() const
{
    return m_parent != nullptr && m_parent->getLeft() == this;
}

bool BinaryTree::Node::isRight() const
{
    return m_parent != nullptr && m_parent->getRight() == this;
}

BinaryTree::BinaryTree()
{
    m_root = nullptr;
}

BinaryTree::Node *BinaryTree::getRoot()
{
    return m_root;
}

const BinaryTree::Node *BinaryTree::getRoot() const
{
    return m_root;
}

void BinaryTree::deleteTree(BinaryTree::Node *node)
{
    if (node == nullptr)
        return;
    this->deleteTree(node->getLeft());
    this->deleteTree(node->getRight());
    Node* parent = node->getParent();
    if (parent != nullptr)
    {
        if (parent->getLeft() == node)
            parent->m_setLeft(nullptr);
        else if (parent->getRight() == node)
            parent->m_setRight(nullptr);
    }
    if (node == m_root)
        m_root = nullptr;
    delete node;
}

void BinaryTree::deleteTree()
{
    this->deleteTree(this->getRoot());
}

BinaryTree::~BinaryTree()
{
    this->deleteTree();
}

bool BinaryTree::isEmpty() const
{
    return m_root == nullptr;
}

BinaryTree BinaryTree::copyTree(const BinaryTree::Node *node) const
{
    BinaryTree tree;
    tree.m_root = this->m_copyTree(node);
    return tree;
}

BinaryTree::Node *BinaryTree::m_copyTree(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return nullptr;
    Node* new_node = new Node(node->getKey(), nullptr, nullptr, nullptr);
    Node* left = this->m_copyTree(node->getLeft()), *right = this->m_copyTree(node->getRight());
    Node::setLeftConnection(new_node, left);
    Node::setRightConnection(new_node, right);
    return new_node;
}

BinaryTree::BinaryTree(const BinaryTree &tree)
{
    m_root = tree.m_copyTree(tree.getRoot());
}

int BinaryTree::getHeight() const
{
    return this->getHeight(this->getRoot());
}

int BinaryTree::getHeight(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return 0;
    return 1 + std::max(this->getHeight(node->getLeft()), this->getHeight(node->getRight()));
}

int BinaryTree::getNodeCount() const
{
    return this->getNodeCount(this->getRoot());
}

int BinaryTree::getNodeCount(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return 0;
    return 1 + this->getNodeCount(node->getLeft()) + this->getNodeCount(node->getRight());
}

int BinaryTree::getMinKey() const
{
    return this->getMinKey(this->getRoot());
}

int BinaryTree::getMaxKey() const
{
    return this->getMaxKey(this->getRoot());
}

int BinaryTree::getMinKey(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return INT_MAX;
    return std::min(node->getKey(), std::min(this->getMinKey(node->getLeft()), this->getMinKey(node->getRight())));
}

int BinaryTree::getMaxKey(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return INT_MIN;
    return std::max(node->getKey(), std::max(this->getMaxKey(node->getLeft()), this->getMaxKey(node->getRight())));
}

BinaryTree::Node* BinaryTree::addNode(int key, int priority)
{
    if (m_root == nullptr)
        return m_root = new Node(key);
    else
        return this->addNode(key, this->getRoot(), priority);
}

BinaryTree::Node* BinaryTree::addNode(int key, BinaryTree::Node *node, int priority)
{
    if (node == nullptr)
        return this->addNode(key, priority);
    int choice;
    Node* children[2] = { node->getLeft(), node->getRight() };
    if (children[priority] == nullptr)
        choice = priority;
    else if (children[1 - priority] == nullptr)
        choice = 1 - priority;
    else
        choice = rand() % 2;
    if (children[choice] != nullptr)
        return this->addNode(key, children[choice], priority);
    Node* new_node = new Node(key);
    if (choice == 0)
        Node::setLeftConnection(node, new_node);
    else
        Node::setRightConnection(node, new_node);
    return new_node;
}

void BinaryTree::print(int marginLeft, int levelSpacing) const
{
    this->print(this->getRoot(), marginLeft, levelSpacing);
}

void BinaryTree::print(const BinaryTree::Node *node, int marginLeft, int levelSpacing) const
{
    if (node == nullptr)
        return;
    this->print(node->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << node->getKey() << '\n';
    this->print(node->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree::Node *BinaryTree::find(int key)
{
    return this->find(key, this->getRoot());
}

const BinaryTree::Node *BinaryTree::find(int key) const
{
    return this->find(key, this->getRoot());
}

const BinaryTree::Node *BinaryTree::find(int key, const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return nullptr;
    if (node->getKey() == key)
        return node;
    const Node* left = find(key, node->getLeft());
    if (left == nullptr)
        return find(key, node->getRight());
    return left;
}

BinaryTree::Node *BinaryTree::find(int key, const BinaryTree::Node *node)
{
    return const_cast<BinaryTree::Node*>(const_cast<const BinaryTree*>(this)->find(key, node));
}

bool BinaryTree::deleteNode(int key)
{
    return this->deleteNode(key, this->getRoot());
}

bool BinaryTree::deleteNode(int key, BinaryTree::Node *node)
{
    Node* nodeToDelete = this->find(key, node);
    if (nodeToDelete == nullptr)
        return false;
    this->deleteNode(nodeToDelete, node);
    return true;
}

void BinaryTree::deleteNode(BinaryTree::Node *nodeToDelete, BinaryTree::Node *node)
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
    Node* nodeReplacement = node;
    while (nodeReplacement->getChildrenCount() != 0) {
        if (nodeReplacement->getLeft() == nullptr)
            nodeReplacement = nodeReplacement->getRight();
        else
            nodeReplacement = nodeReplacement->getLeft();
    }
    nodeToDelete->setKey(nodeReplacement->getKey());
    this->deleteNode(nodeReplacement, node);
}

bool BinaryTree::isBalanced() const
{
    return this->isBalanced(this->getRoot());
}

bool BinaryTree::isBalanced(const BinaryTree::Node *node) const
{
    return this->getInfo(node).balanced;
}

BinaryTree::Info BinaryTree::getInfo() const
{
    return this->getInfo(this->getRoot());
}

BinaryTree::Info BinaryTree::getInfo(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return { true, 0, 0 };
    Info leftInfo = this->getInfo(node->getLeft()), rightInfo = this->getInfo(node->getRight());
    Info info{};
    info.balanced = leftInfo.balanced && rightInfo.balanced;
    info.balanced = info.balanced && std::abs(leftInfo.height - rightInfo.height) <= 1;
    info.balanced = info.balanced && std::abs(leftInfo.nodeCount - rightInfo.nodeCount) <= 1;
    info.nodeCount = 1 + leftInfo.nodeCount + rightInfo.nodeCount;
    info.height = 1 + std::max(leftInfo.height, rightInfo.height);
    return info;
}

int BinaryTree::getKeySum() const
{
    return this->getKeySum(this->getRoot());
}

int BinaryTree::getKeySum(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return 0;
    return node->getKey() + this->getKeySum(node->getLeft()) + this->getKeySum(node->getRight());
}

int BinaryTree::getLevelIndex(int key) const
{
    return this->getLevelIndex(key, this->getRoot());
}

int BinaryTree::getLevelIndex(int key, const BinaryTree::Node *node) const
{
    const Node* nodeFind = this->find(key, node);
    if (nodeFind == nullptr)
        return -1;
    int index = 0;
    while (nodeFind != m_root) {
        nodeFind = nodeFind->getParent();
        ++index;
    }
    return index;
}

std::vector<int> BinaryTree::getKeys() const
{
    return this->getKeys(this->getRoot());
}

std::vector<int> BinaryTree::getKeys(const BinaryTree::Node *node) const
{
    std::vector<int> res;
    res.reserve(this->getNodeCount());
    for (ConstIterator it(node); !it.isEnd(); it.next())
        res.push_back(it.getCurrentNode()->getKey());
    return res;
}

void BinaryTree::printLevel(int index) const
{
    this->printLevel(index, this->getRoot());
}

void BinaryTree::printLevel(int index, const BinaryTree::Node *node) const
{
    if (index == 0 && node != nullptr) {
        std::cout << node->getKey() << ' ';
        return;
    }
    if (node == nullptr) {
        int it_count = (1 << index);
        for (int i = 0; i < it_count; ++i)
            std::cout << 'N' << ' ';
        return;
    }
    this->printLevel(index - 1, node->getLeft());
    this->printLevel(index - 1, node->getRight());
}

void BinaryTree::printLevels() const
{
    this->printLevels(this->getRoot());
}

void BinaryTree::printLevels(const BinaryTree::Node *node) const
{
    int height = this->getHeight(node);
    for (int level = 0; level < height; ++level) {
        this->printLevel(level, node);
        std::cout << '\n';
    }
}

void BinaryTree::printLeaves() const
{
    this->printLeaves(this->getRoot());
}

void BinaryTree::printLeaves(const BinaryTree::Node *node) const
{
    if (node == nullptr)
        return;
    if (node->getChildrenCount() == 0)
        std::cout << node->getKey() << ' ';
    this->printLeaves(node->getLeft());
    this->printLeaves(node->getRight());
}

BinaryTree &BinaryTree::operator=(const BinaryTree &tree)
{
    if (&tree == this)
        return *this;
    this->deleteTree();
    this->m_root = tree.m_copyTree(tree.m_root);
    return *this;
}

void BinaryTree::deleteSubtrees()
{
    this->deleteSubtrees(this->getRoot());
}

void BinaryTree::deleteSubtrees(BinaryTree::Node *node)
{
    if (node == nullptr)
        return;
    this->deleteTree(node->getLeft());
    this->deleteTree(node->getRight());
}

BinaryTree::ConstIterator::ConstIterator(const BinaryTree &tree)
{
    if (!tree.isEmpty())
        this->m_queue.push(tree.getRoot());
}

void BinaryTree::ConstIterator::init(const BinaryTree &tree)
{
    while (!m_queue.empty())
        m_queue.pop();
    if (!tree.isEmpty())
        this->m_queue.push(tree.getRoot());
}

const BinaryTree::Node *BinaryTree::ConstIterator::getCurrentNode() const
{
    return m_queue.front();
}

void BinaryTree::ConstIterator::next()
{
    const Node* node = this->getCurrentNode();
    if (node->getLeft() != nullptr)
        m_queue.push(node->getLeft());
    if (node->getRight() != nullptr)
        m_queue.push(node->getRight());
    m_queue.pop();
}

bool BinaryTree::ConstIterator::isEnd() const
{
    return m_queue.empty();
}

BinaryTree::ConstIterator::ConstIterator(const BinaryTree::Node *node)
{
    if (node != nullptr)
        this->m_queue.push(node);
}

void BinaryTree::ConstIterator::init(const BinaryTree::Node *node)
{
    while (!m_queue.empty())
        m_queue.pop();
    if (node != nullptr)
        this->m_queue.push(node);
}

bool BinaryTree::ConstIterator::hasNext() const
{
    return !m_queue.empty();
}

BinaryTree::ConstLnrIterator::ConstLnrIterator(const BinaryTree &tree)
{
    m_currentNode = nullptr;
    m_root = nullptr;
    this->init(tree.getRoot());
}

BinaryTree::ConstLnrIterator::ConstLnrIterator(const BinaryTree::Node *node)
{
    m_currentNode = nullptr;
    m_root = nullptr;
    this->init(node);
}

void BinaryTree::ConstLnrIterator::init(const BinaryTree &tree)
{
    this->init(tree.getRoot());
}

void BinaryTree::ConstLnrIterator::init(const BinaryTree::Node *node)
{
    m_root = node;
    m_currentNode = node;
    if (m_currentNode != nullptr) {
        while (m_currentNode->getLeft() != nullptr)
            m_currentNode = m_currentNode->getLeft();
    }
}

const BinaryTree::Node *BinaryTree::ConstLnrIterator::getCurrentNode() const
{
    return m_currentNode;
}

void BinaryTree::ConstLnrIterator::next()
{
    if (m_currentNode == nullptr)
        return;
    if (m_currentNode->getRight() != nullptr) {
        m_currentNode = m_currentNode->getRight();
        while (m_currentNode->getLeft() != nullptr)
            m_currentNode = m_currentNode->getLeft();
        return;
    }
    while (m_currentNode->isRight() && m_currentNode != m_root)
        m_currentNode = m_currentNode->getParent();
    if (m_currentNode == m_root) {
        m_currentNode = nullptr;
        return;
    }
    m_currentNode = m_currentNode->getParent();
}

bool BinaryTree::ConstLnrIterator::hasNext() const
{
    return m_currentNode != nullptr;
}

bool BinaryTree::ConstLnrIterator::isEnd() const //atEnd
{
    return m_currentNode == nullptr;
}
