#include "HuffmanTree.h"
#include <list>
#include <iostream>

void HuffmanTree::clear()
{
    m_clear(m_root);
    m_root = nullptr;
}

void HuffmanTree::m_clear(HuffmanTree::Node *node)
{
    if (node == nullptr)
        return;
    m_clear(node->left);
    m_clear(node->right);
    delete node;
}

HuffmanTree::HuffmanTree()
{
    m_root = nullptr;
}

void HuffmanTree::build(const std::string &text)
{
    clear();
    int frequencies[256] = {};
    for (int i = 0; i < text.length(); ++i)
        ++frequencies[text[i]];
    std::list<Node*> nodes;
    for (int i = 0; i < 256; ++i) {
        if (frequencies[i] == 0)
            continue;
        Node* new_node = new Node;
        new_node->frequency = frequencies[i];
        new_node->symbols.insert(i);
        nodes.push_back(new_node);
    }
    while (nodes.size() > 1) {
        nodes.sort([](Node* first, Node* second) {
            return first->frequency < second->frequency;
        });
        Node *first, *second;
        first = *(nodes.begin());
        nodes.pop_front();
        second = *(nodes.begin());
        nodes.pop_front();
        Node *root = new Node;
        root->left = first;
        root->right = second;
        root->frequency = first->frequency + second->frequency;
        root->symbols.insert(first->symbols.begin(), first->symbols.end());
        root->symbols.insert(second->symbols.begin(), second->symbols.end());
        nodes.push_back(root);
    }
    m_root = *(nodes.begin());
}

HuffmanTree::~HuffmanTree()
{
    clear();
}

void HuffmanTree::printNodes() const
{
    m_printNodes(m_root);
}

void HuffmanTree::m_printNodes(HuffmanTree::Node *node) const
{
    if (node == nullptr)
        return;
    m_printNodes(node->left);
    node->print();
    std::cout << '\n';
    m_printNodes(node->right);
}

double HuffmanTree::encode(const std::string &text, std::string &encoded)
{
    if (m_root == nullptr)
        build(text);
    encoded = "";
    for (char c : text) {
        if (!(m_root->symbols.contains(c)))
            return -1;
        if (m_root->symbols.size() == 1)
        {
            encoded.push_back('0');
            continue;
        }
        Node* node = m_root;
        while (node->symbols.size() > 1) {
            if (node->left != nullptr && node->left->symbols.contains(c)) {
                encoded.push_back('0');
                node = node->left;
            }
            else {
                encoded.push_back('1');
                node = node->right;
            }
        }
    }
    return double(encoded.size()) / double(text.size() * 8);
}

bool HuffmanTree::decode(const std::string &encoded, std::string &decoded)
{
    decoded = "";
    Node* node = m_root;
    if (node == nullptr)
        return false;
    for (char c : encoded) {
        if (m_root->symbols.size() == 1) {
            if (c != '0')
                return false;
            decoded += *(node->symbols.begin());
            continue;
        }
        if (c == '0')
            node = node->left;
        else if (c == '1')
            node = node->right;
        else
            return false;
        if (node == nullptr)
            return false;
        else if (node->symbols.size() == 1) {
            decoded += *(node->symbols.begin());
            node = m_root;
        }
    }
    return node == m_root;
}

void HuffmanTree::Node::print()
{
    std::cout << "Frequency: " << frequency << '\n';
    std::cout << "Symbols: ";
    for (char c : symbols)
        std::cout << '\'' << c << "\' ";
    std::cout << '\n';
}
