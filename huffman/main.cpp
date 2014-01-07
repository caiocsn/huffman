#include <Tree.h>
#include <File.h>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>

int main(int argc, char *argv[])
{

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
    Tree * t = new Tree(root);
    Node * b = new Node('B');
    Node * n4 = new Node();
    root->setRight(b);
    root->setLeft(n4);
    Node * a = new Node('A');
    Node * c = new Node('C');
    n4->setLeft(a);
    n4->setRight(c);
    qDebug() << "show";
    t->showTree();
    t->createRep();

    return 0;
}
