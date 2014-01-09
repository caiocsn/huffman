#include "CreateHuffmanTree.h"

CreateHuffmanTree::CreateHuffmanTree(Queue * occur) {
    m_occurrences = occur;
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
        n3->setRight(n1);
        n3->setLeft(n2);
        m_occurrences->enqueue(n3);
        root = n3;
    }
    return t;
}
