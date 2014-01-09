#ifndef CREATEHUFFMANTREE_H
#define CREATEHUFFMANTREE_H

#include <Node.h>
#include <Tree.h>
#include <Queue.h>
#include <QList>
#include <Occurrence.h>

class CreateHuffmanTree
{
public:
    CreateHuffmanTree(QList<Occurrence> oc);
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
