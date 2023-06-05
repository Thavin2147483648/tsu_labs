#pragma once
#include <set>
#include <string>

class HuffmanTree
{
public:
    HuffmanTree();
    ~HuffmanTree();
    void clear();
    void printNodes() const;
    void build(const std::string& text);
    double encode(const std::string& text, std::string& encoded);
    bool decode(const std::string& encoded, std::string& decoded);

private:
    struct Node
    {
        Node* left = nullptr;
        Node* right = nullptr;
        int frequency = 0;
        std::set<char> symbols;

        void print();
    };

private:
    Node* m_root;

private:
    void m_clear(Node* node);
    void m_printNodes(Node* node) const;
};
