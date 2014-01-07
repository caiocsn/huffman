# include <QDebug>
# include <Tree.h>
# include <QString>

Tree::Tree() {
    m_root = 0;
}

Tree::Tree(Node * root) {
    m_root = root;
}

Tree::Tree (QString rep) {

}

Tree::~Tree () {
    delete m_root;
}

void Tree::showTree() {
    preOrder(m_root);
}

QString Tree::createRep () {
    preOrderRep(m_root);
    qDebug() << "tree " << m_rep;
}

Node * Tree::root() {
    return m_root;
}

void Tree::setRoot (Node * newRoot) {
    m_root = newRoot;
}

void Tree::preOrder(Node *node) {
    if (node) {
        preOrder(node->left());
        this->visit(node);
        preOrder(node->right());
    }
}

void Tree::visit(Node *node) {
    QString str = "";
    if (node->key() != 0) {
        str.append(node->key());
    } else {
        str.append("[]");
    }
    for(int i = 0; i < node->height(); ++i) {
        str.prepend("\t");
    }
    qDebug() << str;
}

void Tree::preOrderRep(Node *node) {
    if (node) {
        if (node->left()) m_rep.append("(");
        preOrderRep(node->left());
        this->visitRep(node);
        if (node->right()) m_rep.append(")");
        preOrderRep(node->right());
    }
}

void Tree::visitRep(Node *node) {
    if (node->key() != 0) m_rep.append(node->key());
}
