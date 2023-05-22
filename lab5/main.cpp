#include <iostream>
#include "HuffmanTree.h"

int main()
{
    std::string text = "abracadabra", encoded, decoded;
    HuffmanTree tree;
    std::cout << tree.encode(text, encoded) << '\n';
    std::cout << encoded << '\n';
    std::cout << tree.decode(encoded, decoded) << '\n';
    std::cout << decoded << '\n';
    return 0;
}