#ifndef TREE_H
#define TREE_H

# include <QString>
# include <Node.h>
# include <QStack>

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
    QString rep ();
private:
    void preOrder(Node * node);
    void visit(Node * node);
    void preOrderRep(Node * node);
    void visitRep(Node * node);
    //void verifyChar(QString characters, QStack<char> stack, Node * granRoot, Node * root);
    void verifyChar(QString characters, Node * granRoot, Node * root);
private:
    Node * m_root;
    QString m_rep;
};

#endif // TREE_H
