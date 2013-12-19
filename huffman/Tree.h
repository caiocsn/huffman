#ifndef TREE_H
#define TREE_H

# include <QString>
# include <Node.h>

class Tree {
public:
    Tree();
    Tree(Node * m_root);
    ~Tree();
    void showTree();
    QString createRep ();
    void createTree (QString rep);
    Node * m_root();
    void setRoot (Node * newRoot);
private:
    void preOrder(Node * node);
    void visit(Node * node);
public:
    Node * m_root;
};

#endif // TREE_H
