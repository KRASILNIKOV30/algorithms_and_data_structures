#include "Tree.h"
#include <stdexcept>

Tree::Tree()
{
}

Tree::~Tree()
{
    DeleteNode(root);
}

void Tree::Insert(int key, std::streampos data)
{
    if (root == nullptr) {
        BNode* newRoot = new BNode;
        newRoot->keys[0] = key;
        for (int j = 1; j <= (2 * t - 1); j++) newRoot->keys[j] = 0;
        for (int i = 0; i <= (2 * t); i++) newRoot->children[i] = nullptr;
        newRoot->count = 1;
        newRoot->countSons = 0;
        newRoot->leaf = true;
        newRoot->parent = nullptr;
        root = newRoot;
    }
    else {
        BNode* ptr = root;
        while (!ptr->leaf) //����� ������� �� ��� ���, ���� ���� �� ����� �������� ������
        { 
            for (int i = 0; i <= (2 * t - 1); i++) //���������� ��� �����
            { 
                if (ptr->keys[i] != 0) 
                {
                    if (key < ptr->keys[i]) 
                    {
                        ptr = ptr->children[i];
                        break;
                    }
                    if ((ptr->keys[i + 1] == 0) && (key > ptr->keys[i])) 
                    {
                        ptr = ptr->children[i + 1]; //�������������� � ������ ���������� �������, ���� ���� �� "��������"
                        break;
                    }
                }
                else break;
            }
        }
        InsertToNode(key, ptr, data);

        while (ptr->count == 2 * t) {
            Restruct(ptr);
            if (ptr == root) {
                break;
            }
        }
    }
}

std::streampos Tree::Search(int key)
{
    return SearchKey(key, this->root);
}

void Tree::Remove(int key)
{
}

void Tree::InsertToNode(int key, BNode* node, std::streampos data)
{
    node->keys[node->count] = key;
    node->data[node->count] = data;
    node->count = node->count + 1;
    Sort(node);
}

void Tree::Sort(BNode* node)
{
    int m;
    std::streampos n;
    for (int i = 0; i < (2 * t - 1); i++) {
        for (int j = i + 1; j <= (2 * t - 1); j++) {
            if ((node->keys[i] != 0) && (node->keys[j] != 0)) {
                if ((node->keys[i]) > (node->keys[j])) {
                    m = node->keys[i];
                    n = node->data[i];
                    node->keys[i] = node->keys[j];
                    node->data[i] = node->data[j];
                    node->keys[j] = m;
                    node->data[j] = n;
                }
            }
            else break;
        }
    }
}

void Tree::Restruct(BNode* node)
{
    if (node->count < (2 * t - 1)) return;

    //������ ���
    BNode* child1 = new BNode;
    int j;
    for (j = 0; j <= t - 2; j++) 
    {
        child1->keys[j] = node->keys[j];
        child1->data[j] = node->data[j];
    }
    for (j = t - 1; j <= (2 * t - 1); j++) child1->keys[j] = 0; // ������������� ���� ��������� ������, ����� �������
    child1->count = t - 1; //���������� ������ � ����
    if (node->countSons != 0) 
    {
        for (int i = 0; i <= (t - 1); i++)
        {
            child1->children[i] = node->children[i];
            child1->children[i]->parent = child1;
        }
        for (int i = t; i <= (2 * t); i++) 
        {
            child1->children[i] = nullptr;
        }
        child1->leaf = false;
        child1->countSons = t - 1; //���������� �������
    }
    else
    {
        child1->leaf = true;
        child1->countSons = 0;
        for (int i = 0; i <= (2 * t); i++) child1->children[i] = nullptr; // ������������� ���� ������� nullptr
    }

    //������ ���
    BNode* child2 = new BNode;
    for (int j = 0; j <= (t - 1); j++) 
    { 
        child2->keys[j] = node->keys[j + t]; 
        child2->data[j] = node->data[j + t];
    }
    for (j = t; j <= (2 * t - 1); j++) child2->keys[j] = 0; // ������������� ���� ��������� ������, ����� �������
    child2->count = t; //���������� ������ � ����
    if (node->countSons != 0) {
        for (int i = 0; i <= (t); i++) {
            child2->children[i] = node->children[i + t];
            child2->children[i]->parent = child2;
        }
        for (int i = t + 1; i <= (2 * t); i++) child2->children[i] = nullptr;
        child2->leaf = false;
        child2->countSons = t; //���������� �������
    }
    else {
        child2->leaf = true;
        child2->countSons = 0;
        for (int i = 0; i <= (2 * t); i++) child2->children[i] = nullptr; // ������������� ���� ������� nullptr
    }

    if (node == root) {
        node->keys[0] = node->keys[t - 1];
        node->data[0] = node->data[t - 1];
        for (int j = 1; j <= (2 * t - 1); j++) node->keys[j] = 0;
        node->children[0] = child1;
        node->children[1] = child2;
        for (int i = 2; i <= (2 * t); i++) node->children[i] = nullptr;
        node->leaf = false;
        node->count = 1;
        node->countSons = 2;
        child1->parent = node;
        child2->parent = node;
    }
    else
    {
        InsertToNode(node->keys[t - 1], node->parent, node->data[t - 1]);
        for (int i = 0; i <= (2 * t); i++) {
            if (node->parent->children[i] == node)
            {
                node->parent->children[i] = nullptr;
            }
        }
        for (int i = 0; i <= (2 * t); i++) {
            if (node->parent->children[i] == nullptr) 
            {
                for (int j = (2 * t); j > (i + 1); j--) 
                {
                    node->parent->children[j] = node->parent->children[j - 1]; 
                }
                node->parent->children[i + 1] = child2;
                node->parent->children[i] = child1;
                break;
            }
        }
        child1->parent = node->parent;
        child2->parent = node->parent;
        node->parent->leaf = false;
        BNode* destructuredNode = node;
        node = node->parent;
        delete destructuredNode;
    }
}

std::streampos Tree::SearchKey(int key, BNode* node)
{
    if (node == nullptr)
    {
        throw std::invalid_argument("");
    }
    if (node->leaf == false)
    {
        int i;
        for (i = 0; i <= (2 * t - 1); i++)
        {
            if (node->keys[i] != 0)
            {
                if (key == node->keys[i])
                {
                    return node->data[i];
                }
                if ((key < node->keys[i])) {
                    return SearchKey(key, node->children[i]);
                    break;
                }
            }
            else break;
        }
        return SearchKey(key, node->children[i]);
    }
    else {
        for (int j = 0; j <= (2 * t - 1); j++)
        {
            if (key == node->keys[j])
            {
                return node->data[j];
            }
        }
        throw std::invalid_argument("");
    }
}

void Tree::DeleteNode(BNode* node)
{
    if (node != nullptr) 
    {
        for (int i = 0; i <= (2 * t - 1); i++) // ��������� �������
        {
            if (node->children[i] != nullptr) // ��������� �������
            {
                DeleteNode(node->children[i]);
            }
            else
            {
                delete node;
                break;
            }
        }
    }
}

void Tree::Remove(int key, BNode* node)
{
}

void Tree::RemoveFromNode(int key, BNode* node)
{
}

void Tree::RemoveLeaf(int key, BNode* node)
{
}

void Tree::Lconnect(BNode* node, BNode* othernode)
{
}

void Tree::Rconnect(BNode* node, BNode* othernode)
{
}

void Tree::Repair(BNode* node)
{
}

void Tree::WriteNode(BNode* node, std::ostream& stream, std::string indent) const
{
    stream << indent;
    for (int i = 0; i < t * 2 - 1; ++i)
    {
        if (node->keys[i] != 0)
        {
            stream << node->keys[i] << " ";
        }
    }
    stream << std::endl;

    for (int i = 0; i < t * 2; ++i)
    {
        if (node->children[i] != nullptr)
        {
            WriteNode(node->children[i], stream, indent + "__");
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const Tree& tree)
{
    tree.WriteNode(tree.root, stream, "");
    return stream;
}
