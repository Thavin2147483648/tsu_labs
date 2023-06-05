#include <iostream>
#include "HashTable.h"

int main()
{
    HashTable table(3);
    table.addKey(6, 10);
    table.print();
    table.addKey(7, 20);
    table.print();
    table.addKey(1, 30);
    table.print();
    std::cout << (table.isKeyExists(7) ? "YES" : "NO") << '\n';
    table.deleteKey(7);
    table.print();
    std::cout << (table.isKeyExists(7) ? "YES" : "NO") << '\n';
    table.deleteKey(10);
    table.print();
    std::cout << table[1] << '\n';
    return 0;
}
