#include <QDebug>
#include "CreateHuffmanTree.h"

CreateHuffmanTree::CreateHuffmanTree(QList<Occurrence> oc) {
    m_occurrences = new Queue();
    for (int i = 0; i < oc.size(); ++i) {
        Node * n = new Node(oc[i].character(), oc[i].count());
        m_occurrences->enqueue(n);
    }
}

CreateHuffmanTree::~CreateHuffmanTree() {
    m_occurrences = 0;
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

        qDebug() << "\n\nn1" << n1->frequency() << n1->key();
        qDebug() << "n2" << n2->frequency() << n2->key();
        qDebug() << "n3" << n3->frequency() << n3->key();

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
