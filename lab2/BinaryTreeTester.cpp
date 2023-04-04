#include "BinaryTreeTester.h"
#include <cassert>
#include <chrono>
#include <thread>

void BinaryTreeTester::test(int size)
{
    m_maxSize = size;
    addAndCount();
    destructor();
    remove();
    clear();
    assign();
    height();
}

void BinaryTreeTester::addAndCount() const
{
    std::cout << "Testing addAndCount()\n";
    BinaryTree tree;
    check_addAndCount(tree, 0);
    for (int i = 0; i < m_maxSize; ++i) {
        tree.addNode(i);
        check_addAndCount(tree, i + 1);
    }
    std::cout << "End testing addAndCount()\n";
}

void BinaryTreeTester::check_addAndCount(const BinaryTree &tree, int size)
{
    assert(tree.getNodeCount() == size);
}

void BinaryTreeTester::destructor()
{
    std::cout << "Testing destructor()\n";
    for (int i = 0; i < 20; ++i) {
        BinaryTree tree;
        for (int j = 0; j < m_maxSize; ++j)
            tree.addNode(j);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "End testing destructor()\n";
}

void BinaryTreeTester::remove()
{
    std::cout << "Testing remove()\n";
    int invalidKey = -1;
    std::vector<int> keys;

    BinaryTree tree;
    tree.deleteNode(invalidKey);

    for (int i = 0; i < m_maxSize; ++i) {
        keys.push_back(i);
        tree.addNode(i);
    }

    while (!keys.empty()) {
        tree.print(2, 4);
        std::cout << "===========================================\n";
        int removedNodeIndex = rand() % keys.size();

        tree.deleteNode(invalidKey);
        check_remove(tree, keys.size());

        tree.deleteNode(keys[removedNodeIndex]);
        keys.erase(keys.begin() + removedNodeIndex);
        check_remove(tree, keys.size());
    }
    tree.print(2, 4);
    tree.deleteNode(invalidKey);
    check_remove(tree, keys.size());
    std::cout << "End testing remove()\n";
}

void BinaryTreeTester::check_remove(const BinaryTree &tree, int size)
{
    assert(tree.getNodeCount() == size);
}

void BinaryTreeTester::height()
{
    height_trivialCases();
    height_longOnlyLeftSubtree();
    height_longOnlyRightSubtree();
    height_longOnlyLeftAndRightSubtrees();
    height_longRandomZigzagSubtrees();
}

void BinaryTreeTester::check_height(const BinaryTree &tree, int height)
{
    assert(tree.getHeight() == height);
}

void BinaryTreeTester::height_trivialCases()
{
    std::cout << "Testing height_trivialCases()\n";
    BinaryTree tree;
    check_height(tree, 0);
    tree.addNode(0);
    check_height(tree, 1);
    std::cout << "End testing height_trivialCases()\n";
}

void BinaryTreeTester::height_longOnlyLeftSubtree()
{
    std::cout << "Testing height_longOnlyLeftSubtree()\n";
    BinaryTree tree;
    tree.addNode(0);
    BinaryTree::Node* runner = tree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        tree.addNode(i, runner, 0);
        runner = runner->getLeft();
        check_height(tree, i + 1);
    }
    tree.print(2, 4);
    std::cout << "End testing height_longOnlyLeftSubtree()\n";
}

void BinaryTreeTester::height_longOnlyRightSubtree()
{
    std::cout << "Testing height_longOnlyRightSubtree()\n";
    BinaryTree tree;
    tree.addNode(0);
    BinaryTree::Node* runner = tree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        tree.addNode(i, runner, 1);
        runner = runner->getRight();
        check_height(tree, i + 1);
    }
    tree.print(2, 4);
    std::cout << "End testing height_longOnlyRightSubtree()\n";
}

void BinaryTreeTester::height_longOnlyLeftAndRightSubtrees()
{
    std::cout << "Testing height_longOnlyLeftAndRightSubtrees()\n";
    BinaryTree tree;
    tree.addNode(0);
    BinaryTree::Node* leftRunner = tree.getRoot(), *rightRunner = tree.getRoot();
    for (int i = 1; i < m_maxSize; ++i) {
        tree.addNode(i, leftRunner, 0);
        leftRunner = leftRunner->getLeft();
        check_height(tree, i + 1);
        tree.addNode(i, rightRunner, 1);
        rightRunner = rightRunner->getRight();
        check_height(tree, i + 1);
    }
    tree.print(2, 4);
    std::cout << "End testing height_longOnlyLeftAndRightSubtrees()\n";
}

void BinaryTreeTester::height_longRandomZigzagSubtrees()
{
    std::cout << "Testing height_longRandomZigzagSubtrees()\n";
    BinaryTree tree;
    tree.addNode(0);
    BinaryTree::Node *leftRunner = tree.getRoot(), *rightRunner = tree.getRoot();
    tree.addNode(1, leftRunner, 0);
    leftRunner = leftRunner->getLeft();
    tree.addNode(1, rightRunner, 1);
    rightRunner = rightRunner->getRight();
    for (int i = 2; i < m_maxSize / 2; ++i) {
        if (rand() % 2 == 0) {
            tree.addNode(i, leftRunner, 0);
            leftRunner = leftRunner->getLeft();
        }
        else {
            tree.addNode(i, leftRunner, 1);
            leftRunner = leftRunner->getRight();
        }
        check_height(tree, i + 1);
        if (rand() % 2 == 0) {
            tree.addNode(i, rightRunner, 0);
            rightRunner = rightRunner->getLeft();
        }
        else {
            tree.addNode(i, rightRunner, 1);
            rightRunner = rightRunner->getRight();
        }
        check_height(tree, i + 1);
    }
    tree.print(2, 4);
    std::cout << "End testing height_longRandomZigzagSubtrees()\n";
}

void BinaryTreeTester::check_clear(const BinaryTree &tree, int size)
{
    assert(tree.getNodeCount() == size);
}

void BinaryTreeTester::check_assign(const BinaryTree::Node *tree1, const BinaryTree::Node *tree2)
{
    if (tree1 == nullptr || tree2 == nullptr) {
        assert(tree1 == nullptr && tree2 == nullptr);
        return;
    }
    assert(tree1 != tree2 && tree1->getKey() == tree2->getKey());
    check_assign(tree1->getLeft(), tree2->getLeft());
    check_assign(tree1->getRight(), tree2->getRight());
}

void BinaryTreeTester::clear()
{
    std::cout << "Testing clear()\n";
    BinaryTree tree;
    for (int i = 0; i < m_maxSize; ++i)
        tree.addNode(i);
    tree.deleteTree();
    check_clear(tree, 0);
    std::cout << "End testing clear()\n";
}

void BinaryTreeTester::assign()
{
    std::cout << "Testing assign()\n";
    BinaryTree tree1;
    for (int i = 0; i < m_maxSize; ++i)
        tree1.addNode(i);
    BinaryTree tree2(tree1);
    check_assign(tree1.getRoot(), tree2.getRoot());
    tree1 = tree2;
    check_assign(tree1.getRoot(), tree2.getRoot());
    std::cout << "End testing assign()\n";
}




