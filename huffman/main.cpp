#include <Tree.h>
#include <File.h>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>

int main() {

//     QFile *f = new QFile("/home/marilia/Downloads/teste.jpg");
//     QByteArray q = f->readAll();

//    File * f = new File("/home/larissartemis/workspace/huffman/huffman/", "teste.txt");
//    QByteArray q = f->read();
//    CountOccurrence * counter = new CountOccurrence(q);
//    counter->count();
//    counter->print();
//    QList<Occurrence> occurrencesOrdered = counter->orderByOccurrence();
//    qDebug() << "done";

    Node * root = new Node();
    Node * l = new Node('L');
    Node * a = new Node('A');
    Node * r = new Node('R');
    Node * i = new Node('I');
    Node * s = new Node('S');
    Node * v1 = new Node();
    Node * v2 = new Node();
    Node * v3 = new Node();

    Tree * t = new Tree(root);
    root->setRight(v1);
    v1->setRight(s);
    v1->setLeft(a);
    root->setLeft(v2);
    v2->setRight(v3);
    v2->setLeft(l);
    v3->setRight(r);
    v3->setLeft(i);

    t->createRep();

    File * f = new File("/home/larissartemis/workspace/huffman/huffman/", "teste.txt");
    QByteArray q = f->read();

    QByteArray byteArray;
    byteArray.append(t->rep());

    f->write(byteArray, t->rep(), 5);
    qDebug() << "done";

    return 0;
}
