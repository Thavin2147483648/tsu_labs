#pragma once
#include "BinaryTree.h"

class BinaryTreeTester
{
public:
    BinaryTreeTester() = default;
    ~BinaryTreeTester() = default;
    void test(int size);
protected:
    static void check_addAndCount(const BinaryTree& tree, int size);
    void check_remove(const BinaryTree& tree, int size);
    void check_clear(const BinaryTree& tree, int size);
    void check_assign(const BinaryTree::Node* tree1, const BinaryTree::Node* tree2);
    void check_height(const BinaryTree& tree, int height);
private:
    int m_maxSize;

    void addAndCount() const;
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