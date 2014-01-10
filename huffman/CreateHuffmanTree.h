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
    CreateHuffmanTree();
    CreateHuffmanTree(QList<Occurrence> oc);
    ~CreateHuffmanTree();
    Queue * occurrence();
    void setOccurence(Queue * occur);
    Tree * tree();
    void setTree(Tree * t);
    Tree * createTree();
   // void setHash(QHash<Node *, QString> * hash);
    void setHash(QHash<char, QString> * hash);
    //QHash<Node *, QString> * hash();
    QHash<char, QString> * hash();
    void createHash(Tree * t);
    void showHash();

private:
    void addNodeToHash(Node * node, QString path);
    void addNodeToHash(char key, QString path);

private:
    Queue * m_occurrences;
    Tree * m_tree;
    //QHash<Node *, QString> * m_hash;
    QHash<char, QString> * m_hash;
};

#endif // CREATEHUFFMANTREE_H
