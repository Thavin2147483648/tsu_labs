#include <iostream>
#include "BinaryTree.h"
using std::cin, std::cout;

int main()
{
    srand(time(nullptr));
    BinaryTree tree;
    for (int i = 1; i <= 10; ++i)
        tree.addNode(i);
    tree.print(2, 4);
    tree.printLevels();
    return 0;
}
