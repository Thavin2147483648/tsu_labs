#include <iostream>
#include "..\lab2\BinaryTree.h"
#include "BinarySearchTree.h"
using std::cin, std::cout;

int main()
{
    srand(time(nullptr));
    int values[12] = { 50, 20, 70, 10, 30, 60, 90, 5, 15, 40, 35, 45 };
    BinarySearchTree tree;
    for (int i = 0; i < 12; ++i)
        tree.addNode(values[i]);
    tree.print(2, 4);
    cout << "Delete\n";
    tree.deleteNode(50);
    tree.print(2, 4);
    cout << '\n';
    return 0;
}