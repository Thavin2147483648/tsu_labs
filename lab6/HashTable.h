#pragma once
#include <list>
#include <utility>

class HashTable
{
public:
    HashTable();
    HashTable(int n);
    HashTable(const HashTable& hash_table);
    ~HashTable();
    void addKey(int key, int value);
    void deleteKey(int key);
    bool isKeyExists(int key) const;
    void print() const;
    HashTable& operator =(const HashTable& hash_table);
    int& operator[](int key);

private:
    int m_hashFunction(int key) const;
    static void m_processSize(int size);

private:
    int m_size;
    std::list<std::pair<int, int>> *m_table;
};
