# include <Tree.h>
# include <QString>

Tree::Tree() {
    this->m_root = 0;
}

Tree::Tree(Node * root) {
    this->m_root = root;
}

Tree::~Tree () {
    delete this->m_root;
}

void Tree::showTree() {
    this->preOrder(m_root);
}

QString Tree::createRep ();

void Tree::createTree (QString rep);

Node * Tree::m_root() {
    return this->m_root;
}

void Tree::setRoot (Node * newRoot) {
    this->m_root = newRoot;
}

void Tree::preOrder(Node *node) {
    if (node) {
        // qDebug() << node->getKey();
        preOrder(node->getLeft());
        this->visit(node);
        preOrder(node->getRight());
    }
}

void Tree::visit(Node *node) {
    QString str = QString::number(node->getKey());
    for(int i = 0; i < node->getHeight(); ++i) {
        str.prepend("\t");
    }
    qDebug() << str;
}
