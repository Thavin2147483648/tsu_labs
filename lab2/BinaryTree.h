#pragma once
#include <iostream>
#include <vector>
#include <queue>

class BinarySearchTree;

class BinaryTree {
public:
    struct Info {
        bool balanced;
        int nodeCount;
        int height;
    };

    class Node {
    public:
        const Node* getParent() const;
        const Node* getLeft() const;
        const Node* getRight() const;
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        int getKey() const;
        void setKey(int key);
        int getChildrenCount() const;
        bool isLeft() const;
        bool isRight() const;
    private:
        Node* m_parent;
        Node* m_left;
        Node* m_right;
        int m_key;

        static void setLeftConnection(Node* parent, Node* left);
        static void setRightConnection(Node* parent, Node* right);
        explicit Node(int key = 0, Node *m_parent = nullptr, Node *m_left = nullptr, Node *m_right = nullptr);
        void m_setParent(Node *parent);
        void m_setLeft(Node *left);
        void m_setRight(Node *right);

        friend class BinaryTree;
        friend class BinarySearchTree;
    };

    class ConstIterator {
    public:
        explicit ConstIterator(const BinaryTree& tree);
        explicit ConstIterator(const Node* node);
        void init(const BinaryTree& tree);
        void init(const Node* node);
        const Node* getCurrentNode() const;
        void next();
        bool hasNext() const;
        bool isEnd() const; //hasNext
    private:
        std::queue<const Node*> m_queue;
    };

    class ConstLnrIterator {
    public:
        explicit ConstLnrIterator(const BinaryTree& tree);
        explicit ConstLnrIterator(const Node* node);
        void init(const BinaryTree& tree);
        void init(const Node* node);
        const Node* getCurrentNode() const;
        void next();
        bool hasNext() const;
        bool isEnd() const;
    private:
        const Node* m_root;
        const Node* m_currentNode;
    };

    BinaryTree();
    BinaryTree(const BinaryTree& tree);
    virtual ~BinaryTree();
    Node* getRoot();
    const Node* getRoot() const;
    void deleteTree();
    void deleteTree(Node* node);
    void deleteSubtrees();
    void deleteSubtrees(Node* node);
    bool isEmpty() const;
    BinaryTree copyTree(const Node* node) const;
    int getHeight() const;
    int getHeight(const Node* node) const;
    int getNodeCount() const;
    int getNodeCount(const Node* node) const;
    int getMinKey() const;
    int getMaxKey() const;
    virtual int getMinKey(const Node* node) const;
    virtual int getMaxKey(const Node* node) const;
    Node* addNode(int key, int priority = 0);
    virtual Node* addNode(int key, Node* node, int priority = 0);
    void print(int marginLeft, int levelSpacing) const;
    void print(const Node* node, int marginLeft, int levelSpacing) const;
    Node* find(int key);
    virtual const Node* find(int key) const;
    Node* find(int key, const Node* node);
    virtual const Node* find(int key, const Node* node) const;
    bool deleteNode(int key);
    bool deleteNode(int key, Node* node);
    virtual void deleteNode(Node* nodeToDelete, Node* node);
    bool isBalanced() const;
    bool isBalanced(const Node* node) const;
    Info getInfo() const;
    Info getInfo(const Node* node) const;
    int getKeySum() const;
    int getKeySum(const Node* node) const;
    int getLevelIndex(int key) const;
    virtual int getLevelIndex(int key, const Node* node) const;
    std::vector<int> getKeys() const;
    std::vector<int> getKeys(const Node* node) const;
    void printLevel(int index) const;
    void printLevel(int index, const Node* node) const;
    void printLevels() const;
    void printLevels(const Node* node) const;
    void printLeaves() const;
    void printLeaves(const Node* node) const;

    BinaryTree& operator =(const BinaryTree& tree);
protected:
    Node* m_root;

    Node* m_copyTree(const Node* node) const;
};
