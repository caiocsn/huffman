#include <Tree.h>
#include <File.h>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <QFile>
#include <CountOccurrence.h>
#include <CreateHuffmanTree.h>

int main() {
    Tree * teste = new Tree("(ac)b");
    teste->showTree();


    File * f = new File("/home/larissartemis/workspace/huffman/huffman/", "teste.txt");
    QByteArray q = f->read();
    CountOccurrence * co = new CountOccurrence(q);
    qDebug() << "counted";
    QList<Occurrence> occur = co->orderByOccurrence();
    qDebug() << "ordered" << co->orderByOccurrence().size();
    CreateHuffmanTree * cht = new CreateHuffmanTree(occur);
    qDebug() << "created cht";
    Tree * t = cht->createTree();
    qDebug() << "created t";
    t->showTree();
    QString rep = t->rep();
    qDebug() << rep;

    // codificado
    // QByteArray cod;
    // int gSize;

    // f->write(cod, rep, gSize);

    QByteArray byteArray;
    byteArray.append(t->rep());

    f->write(byteArray, t->rep(), 5);

    qDebug() << "done";


    return 0;
}
