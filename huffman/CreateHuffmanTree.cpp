#include <QDebug>
#include "CreateHuffmanTree.h"

CreateHuffmanTree::CreateHuffmanTree(QList<Occurrence> oc) {
    m_hash = new QHash<Node *, QString>();
    m_occurrences = new Queue();
    for (int i = 0; i < oc.size(); ++i) {
        Node * n = new Node(oc[i].character(), oc[i].count());
        m_occurrences->enqueue(n);
    }
}

CreateHuffmanTree::CreateHuffmanTree() {
    m_hash = new QHash<Node *, QString>();
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
        n3->setRight(n2);
        n3->setLeft(n1);
        m_occurrences->enqueue(n3);
        root = n3;
    }
    t->setRoot(root);
    int h = t->setHeight(root);
    root->setHeight(h);
    qDebug() << root->height();
    return t;
}

void CreateHuffmanTree::setHash(QHash<Node *, QString> * hash) {
    m_hash = hash;
}

QHash<Node*, QString> * CreateHuffmanTree::hash() {
    return m_hash;
}

void CreateHuffmanTree::createHash(Tree *t) {

    addNodeToHash(t->root(), "");

}

void CreateHuffmanTree::addNodeToHash(Node *node, QString path) {
    if (node->isLeaf()) {
        m_hash->insert(node, path);
    } else {
        // call addNode to hash passing right and left node
        if (node->left()) {
            addNodeToHash(node->left(), node->left()->path());
        }

        if (node->right()) {
            addNodeToHash(node->right(), node->right()->path());
        }
    }
}


void CreateHuffmanTree::showHash() {
    QList<Node*> nodes = m_hash->keys();
    for (int i = 0; i < nodes.size(); ++i) {
        qDebug() << nodes[i]->key();
        qDebug() << nodes[i]->path();

    }
}
