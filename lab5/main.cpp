#include <iostream>
#include "HuffmanTree.h"

void test(std::string text)
{
    std::cout << "=========== " << text << " =============" << '\n';
    std::string encoded, decoded;
    HuffmanTree tree;
    std::cout << tree.encode(text, encoded) << '\n';
    std::cout << encoded << '\n';
    std::cout << tree.decode(encoded, decoded) << '\n';
    std::cout << decoded << '\n';
}
int main()
{
    test("abracadabra");
    test("abra");
    test("1110100101001");
    test("1111111111111");
    return 0;
}