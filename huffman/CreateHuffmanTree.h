#ifndef CREATEHUFFMANTREE_H
#define CREATEHUFFMANTREE_H

#include <Node.h>
#include <Tree.h>
#include <Queue.h>

class CreateHuffmanTree
{
public:
    CreateHuffmanTree(Queue * occur);
    ~CreateHuffmanTree();
    Queue * occurrence();
    void setOccurence(Queue * occur);
    Tree * tree();
    void setTree(Tree * t);
    Tree * createTree();
private:
    Queue * m_occurrences;
    Tree * m_tree;
};

#endif // CREATEHUFFMANTREE_H
