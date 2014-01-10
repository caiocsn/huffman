#include <QDebug>
#include "CreateHuffmanTree.h"

CreateHuffmanTree::CreateHuffmanTree(QList<Occurrence> oc) {
//    m_hash = new QHash<Node *, QString>();
    m_hash = new QHash<char, QString>();
    m_occurrences = new Queue();
    for (int i = 0; i < oc.size(); ++i) {
        Node * n = new Node(oc[i].character(), oc[i].count());
        m_occurrences->enqueue(n);
    }
}

CreateHuffmanTree::CreateHuffmanTree() {
//    m_hash = new QHash<Node *, QString>();
    m_hash = new QHash<char, QString>();
    m_occurrences = new Queue();
}

CreateHuffmanTree::~CreateHuffmanTree() {
    m_occurrences = 0;
    //m_hash = NULL;
    delete m_tree;
}

Queue * CreateHuffmanTree::occurrence() {
    return m_occurrences;
}

void CreateHuffmanTree::setOccurence(Queue * occur) {
    m_occurrences = occur;
}

Tree * CreateHuffmanTree::tree() {
    return m_tree;
}

void CreateHuffmanTree::setTree(Tree * t) {
    m_tree = t;
}

Tree * CreateHuffmanTree::createTree() {
    Tree * t = new Tree();
    Node * root;
    while (m_occurrences->length() > 1) {
        Node * n1 = m_occurrences->frontValue();
        m_occurrences->dequeue();
        Node * n2 = m_occurrences->frontValue();
        m_occurrences->dequeue();
        Node * n3 = new Node();
        int n3freq = n1->frequency() + n2->frequency();
        n3->setFrequency(n3freq);
        n3->setRight(n1);
        n3->setLeft(n2);
        m_occurrences->enqueue(n3);
        root = n3;
    }
    t->setRoot(root);
    int h = t->setHeight(root);
    root->setHeight(h);
    qDebug() << root->height();
    return t;
}

//void CreateHuffmanTree::setHash(QHash<Node *, QString> * hash) {
void CreateHuffmanTree::setHash(QHash<char, QString> * hash) {
    m_hash = hash;
}

//QHash<Node*, QString> * CreateHuffmanTree::hash() {
  //  return m_hash;
//}
QHash<char, QString> * CreateHuffmanTree::hash() {
    return m_hash;
}

void CreateHuffmanTree::createHash(Tree *t) {

    addNodeToHash(t->root(), "");

}

void CreateHuffmanTree::addNodeToHash(Node *node, QString path) {
    if (node->isLeaf()) {
        //m_hash->insert(node, path);
        addNodeToHash(node->key(), path);
    } else {
        // call addNode to hash passing right and left node
        if (node->left()) {
            QString path = node->path();
            path.append("0");
            node->left()->setPath(path);
            addNodeToHash(node->left(), node->left()->path());
        }

        if (node->right()) {
            QString path = node->path();
            path.append("1");
            node->right()->setPath(path);
            addNodeToHash(node->right(), node->right()->path());
        }
    }
}

void CreateHuffmanTree::addNodeToHash(char key, QString path) {
        m_hash->insert(key, path);
}


void CreateHuffmanTree::showHash() {
    //QList<Node*> nodes = m_hash->keys();
    QList<char> keys = m_hash->keys();
    for (int i = 0; i < keys.size(); ++i) {
        qDebug() << keys[i];
        qDebug() << m_hash->take(keys[i]);
       // qDebug() << nodes[i]->key();
       // qDebug() << nodes[i]->path();

    }
}
