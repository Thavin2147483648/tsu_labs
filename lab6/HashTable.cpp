#include "HashTable.h"
#include <algorithm>
#include <iostream>

HashTable::HashTable(int n)
{
    m_processSize(n);
    m_size = n;
    m_table = new std::list<std::pair<int, int>>[m_size];
}

HashTable::HashTable() : HashTable(3) {}

HashTable::HashTable(const HashTable &hash_table) : HashTable(hash_table.m_size)
{
    for (int i = 0; i < m_size; ++i)
        m_table[i] = hash_table.m_table[i];
}

HashTable::~HashTable()
{
    delete[] m_table;
}

void HashTable::addKey(int key, int value)
{
    int hash = m_hashFunction(key);
    for (std::pair<int, int> &i : m_table[hash]) {
        if (i.first == key) {
            i.second = value;
            return;
        }
    }
    m_table[hash].push_back({ key, value });
}

void HashTable::deleteKey(int key)
{
    int hash = m_hashFunction(key);
    for (std::list<std::pair<int, int>>::iterator it = m_table[hash].begin(); it != m_table[hash].end(); ++it) {
        if (it->first == key) {
            m_table[hash].erase(it);
            return;
        }
    }
}

bool HashTable::isKeyExists(int key) const
{
    int hash = m_hashFunction(key);
    for (std::list<std::pair<int, int>>::iterator it = m_table[hash].begin(); it != m_table[hash].end(); ++it) {
        if (it->first == key)
            return true;
    }
    return false;
}

void HashTable::print() const
{
    for (int i = 0; i < m_size; ++i) {
        if (m_table[i].size() == 0)
            continue;
        std::cout << i << ": ";
        for (std::pair<int, int> p : m_table[i])
            std::cout << '(' << p.first << ": " << p.second << ") ";
        std::cout << '\n';
    }
}

HashTable &HashTable::operator=(const HashTable &hash_table)
{
    if (&hash_table == this)
        return *this;
    if (m_size != hash_table.m_size) {
        delete[] m_table;
        m_size = hash_table.m_size;
        m_table = new std::list<std::pair<int, int>>[m_size];
    }
    for (int i = 0; i < m_size; ++i)
        m_table[i] = hash_table.m_table[i];
    return *this;
}

int &HashTable::operator[](int key)
{
    int hash = m_hashFunction(key);
    for (std::pair<int, int> &p : m_table[hash]) {
        if (p.first == key)
            return p.second;
    }
    std::cout << "Key not found\n";
    exit(-1);
}

int HashTable::m_hashFunction(int key) const
{
    return key % m_size + (1 + key % (m_size - 2)) % m_size;
}

void HashTable::m_processSize(int size)
{
    if (size <= 2) {
        std::cout << "Size of table must be greater than 2";
        exit(-1);
    }
}
