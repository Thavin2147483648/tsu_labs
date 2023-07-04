#pragma once
#include <chrono>
#include <random>
#include "BinaryTree.h"

class BinaryTreeTester
{
public:
    BinaryTreeTester();
    virtual ~BinaryTreeTester() = default;
    virtual void test(int size);
protected:
    void generateNumbers();
    virtual BinaryTree* allocateTree();
    void deallocateTree(BinaryTree* tree);
    virtual void check_addAndCount(const BinaryTree& tree, int size);
    virtual void check_remove(const BinaryTree& tree, int size);
    virtual void check_clear(const BinaryTree& tree, int size);
    virtual void check_assign(const BinaryTree::Node* tree1, const BinaryTree::Node* tree2);
    void check_height(const BinaryTree& tree, int height);

    int m_maxSize;
    std::mt19937 m_generator;
    std::vector<int> m_numbers;

    void addAndCount();
    void destructor();
    void remove();
    void clear();
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
};