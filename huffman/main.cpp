#include <Compress.h>

int main() {

//    // Tree * teste = new Tree("b(a(dc))");
//    Tree * teste = new Tree("(((ab)c)(ed))f");
//    //Node * root = teste->root();
//    //teste->setHeight(root);
//    teste->showTree();
//    //qDebug() << teste->root()->left()->right()->path();
//    CreateHuffmanTree * chT = new CreateHuffmanTree();
//    chT->createHash(teste);
//    chT->showHash();

//    File * f = new File("/home/larissartemis/workspace/huffman/huffman/", "teste.txt");
//    // QString texto = "AAABBBBBCC" ;
//    // QByteArray q;
//    // q.append(texto);
//    QByteArray q = f->read();
//    CountOccurrence * co = new CountOccurrence(q);
//    qDebug() << "counted";
//    QList<Occurrence> occur = co->orderByOccurrence();
//    qDebug() << "ordered" << co->orderByOccurrence().size();
//    CreateHuffmanTree * cht = new CreateHuffmanTree(occur);
//    qDebug() << "created cht";
//    Tree * t = cht->createTree();
//    qDebug() << "created t";
//    t->showTree();

//    QString rep = t->rep();
//    qDebug() << rep;
//    cht->createHash(t);
//    qDebug() << "hash";
//    cht->showHash();

//    // codificado
//    // QByteArray cod;
//    // int gSize;

//    // f->write(cod, rep, gSize);

//    QByteArray byteArray;
//    byteArray.append(t->rep());

    //f->write(byteArray, t->rep(), 5);

   //Compress d = Compress("/home/marilia/projetop2/teste.txt");
   Compress c = Compress("/home/marilia/projetop2/compactado.huff");
   //d.compress();
   qDebug() << "done1";
   c.uncompress();
   qDebug() << "done";


    return 0;
}
