#ifndef TREE_H
#define TREE_H

# include <QString>
# include <Node.h>

class Tree {
public:
    Tree();
    Tree(Node * root);
    Tree(QString rep);
    ~Tree();
    void showTree();
    QString createRep ();
    Node * root();
    void setRoot (Node * newRoot);
private:
    void preOrder(Node * node);
    void visit(Node * node);
    void preOrderRep(Node * node);
    void visitRep(Node * node);
public:
    Node * m_root;
    QString m_rep;
};

#endif // TREE_H
