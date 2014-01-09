#ifndef CREATEHUFFMANTREE_H
#define CREATEHUFFMANTREE_H

#include <Node.h>
#include <Tree.h>
#include <Queue.h>
#include <QList>
#include <Occurrence.h>
#include <QHash>

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
    void setHash(QHash hash);
    QHash hash();

private:
    Queue * m_occurrences;
    Tree * m_tree;
    QHash m_hash;
};

#endif // CREATEHUFFMANTREE_H
