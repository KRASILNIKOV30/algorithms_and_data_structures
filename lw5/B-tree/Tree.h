#pragma once
#include <iostream>

const int t = 2;
struct BNode {
    int keys[2 * t];
    std::streampos data[2 * t];
    BNode* children[2 * t + 1];
    BNode* parent;
    int count; //количество ключей
    int countSons; //количество сыновей
    bool leaf;
};

class Tree
{
public:
    Tree();
    ~Tree();
    void Insert(int key, std::streampos data);
    std::streampos Search(int key);
    void Remove(int key);
    friend std::ostream& operator <<(std::ostream& stream, const Tree& tree);

private:
    BNode* root = nullptr;
    void InsertToNode(int key, BNode* node, std::streampos data);
    void Sort(BNode* node);
    void Restruct(BNode* node);
    std::streampos SearchKey(int key, BNode* node);
    void DeleteNode(BNode* node);
    void Remove(int key, BNode* node);
    void RemoveFromNode(int key, BNode* node);
    void RemoveLeaf(int key, BNode* node);
    void Lconnect(BNode* node, BNode* othernode);
    void Rconnect(BNode* node, BNode* othernode);
    void Repair(BNode* node);
    void WriteNode(BNode* node, std::ostream& stream, std::string indent) const;
};
