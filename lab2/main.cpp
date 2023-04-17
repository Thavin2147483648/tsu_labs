#include <iostream>
#include "BinaryTree.h"
#include "BinaryTreeTester.h"
using std::cin, std::cout;

int main()
{
    srand(time(nullptr));
    BinaryTree tree;
    for (int i = 0; i < 1; ++i)
        tree.addNode(i, 1);
    tree.print(2, 4);
    for (BinaryTree::ConstLnrIterator it(tree); it.hasNext(); it.next()) {
        cout << it.getCurrentNode()->getKey() << ' ';
    }
    cout << '\n';
    return 0;
}
