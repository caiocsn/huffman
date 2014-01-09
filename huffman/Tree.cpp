# include <QDebug>
# include <Tree.h>
# include <QString>

Tree::Tree() {
    m_root = 0;
}

Tree::Tree(Node * root) {
    m_root = root;
}

void Tree::verifyChar(QString characters, Node * root) {
    char character = characters.at(0).toLatin1();

    if (character == '(') {
        Node * node = new Node();
        node->setRoot(root);

        if (root->left() == 0) {
            root->setLeft(node);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, node);
            }

        } else {
            root->setRight(node);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, node);
            }
        }
    } else {

        if (character == ')') {

            characters.remove(0,1);

            if(!characters.isEmpty()) {
                verifyChar(characters, root->root());
            }

        } else {

            Node * node = new Node(character);
            node->setRoot(root);

            if (character == '00x0') {
                node->setKey(characters.at(1).toLatin1());
                characters.remove(0,1);
            }

            if (root->left() == 0) {
                root->setLeft(node);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                    verifyChar(characters, root);
                }

            } else {
                root->setRight(node);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                    verifyChar(characters, root);
                }
            }
        }

    }

}

Tree::Tree (QString rep) {
    m_rep = rep;
    Node * root =  new Node();
    verifyChar(rep, root);
    m_root = root;
}

Tree::~Tree () {
    delete m_root;
}

void Tree::showTree() {
    preOrder(m_root);
}

QString Tree::createRep () {
    preOrderRep(m_root);
}

Node * Tree::root() {
    return m_root;
}

void Tree::setRoot (Node * newRoot) {
    m_root = newRoot;
}

QString Tree::rep () {
    // qDebug() << "Tree: " << m_rep;
    createRep();
    return m_rep;

}

int Tree::setHeight(Node * node) {
    if (!node) return -1;
    return 1 + max(setHeight(node->left()), setHeight(node->right()));
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
        if (node->left() && !node->left()->isLeaf()) m_rep.append("(");
        preOrderRep(node->left());
        if (node->left() && !node->left()->isLeaf()) m_rep.append(")");

        if (node->key() != 0) {
            if(node->key() == '(' || node->key() == ')') {
                m_rep.append('00x0');
            }
            m_rep.append(node->key());
        }

        if (node->right() && !node->right()->isLeaf()) m_rep.append("(");
        preOrderRep(node->right());
        if (node->right() && !node->right()->isLeaf()) m_rep.append(")");
    }
}

int Tree::max(int n1, int n2)
{
    if (n1 > n2) return n1;
    else return n2;
}
