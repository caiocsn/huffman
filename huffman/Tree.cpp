# include <Tree.h>
# include <QString>

Tree::Tree() {
    m_root = 0;
}

Tree::Tree(Node * root) {
    m_root = root;
}

Tree::~Tree () {
    delete m_root;
}

void Tree::showTree() {
    preOrder(m_root);
}

QString Tree::createRep () {

}

void Tree::createTree (QString rep) {

}

Node * Tree::root() {
    return m_root;
}

void Tree::setRoot (Node * newRoot) {
    m_root = newRoot;
}

void Tree::preOrder(Node *node) {
    if (node) {
        // qDebug() << node->getKey();
        preOrder(node->left());
        this->visit(node);
        preOrder(node->right());
    }
}

void Tree::visit(Node *node) {
    QString str = QString::number(node->key());
    for(int i = 0; i < node->height(); ++i) {
        str.prepend("\t");
    }
}
