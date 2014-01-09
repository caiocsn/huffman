# include <QDebug>
# include <Tree.h>
# include <QString>
//# include <QStack>

Tree::Tree() {
    m_root = 0;
}

Tree::Tree(Node * root) {
    m_root = root;
}
//void Tree::verifyChar(QString characters, QStack<char> stack, Node * granRoot, Node * root) {
void Tree::verifyChar(QString characters, Node * granRoot, Node * root) {
    char character = characters.at(0).toLatin1();

    if (character == '(') {
        //stack.append('(');
        Node * node = new Node();

        if (root->left() == 0) {
            root->setLeft(node);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                //verifyChar(characters, stack, root, node);
                verifyChar(characters, root, node);
            }

        } else {
            root->setRight(node);
            characters.remove(0,1);

            if(!characters.isEmpty()) {
                //verifyChar(characters, stack, root, node);
                verifyChar(characters, root, node);
            }
        }
    } else {

        if (character == ')') {
            //stack.removeLast();

            characters.remove(0,1);

            if(!characters.isEmpty()) {
                //verifyChar(characters, stack, NULL, granRoot);
                verifyChar(characters, NULL, granRoot);
            }

        } else {
            Node * node = new Node(character);

            if (root->left() == 0) {
                root->setLeft(node);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                    //verifyChar(characters, stack, granRoot, root);
                    verifyChar(characters, granRoot, root);
                }

            } else {
                root->setRight(node);
                characters.remove(0,1);

                if(!characters.isEmpty()) {
                   // verifyChar(characters, stack, granRoot, root);
                    verifyChar(characters, granRoot, root);
                }
            }
        }

    }

}

Tree::Tree (QString rep) {
    m_rep = rep;
    Node * root =  new Node();
    verifyChar(rep, NULL, root);
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

        if (node->key() != 0) m_rep.append(node->key());

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
