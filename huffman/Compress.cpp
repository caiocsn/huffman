#include "Compress.h"
#include <QVariant>
#include <QBitArray>

Compress::Compress(QString pathFile) {
    m_path = pathFile;
    m_fileName = pathFile;
    for (int i = pathFile.size() -1; i >= 0; --i) {
        if (pathFile.at(i) == '/') {
            m_path.remove(i, pathFile.size()-i);
            m_path.append("/");
            m_fileName.remove(0,i+1);
            break;
        }
    }
}

Compress::~Compress() {
}

bool Compress::uncompress() {
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();

    QByteArray nameFile;
    for (int i = 2; i < 130; ++i) {
        if (qba[i] == '#') {
            break;
        }
        nameFile.append(qba.at(i));
    }

    QByteArray size;
    size.append(qba.at(0));
    size.append(qba.at(1));
    qDebug() << "2char " << size;


    /*
     *QString > QBitArray
     *QString str = "123 ABC";
     *foreach( QChar c, str ){
     *qDebug() << c << "=" << c.unicode() << "=" << QString( "%1" ).arg( c.unicode(), 0 , 2 );
     *}
     */

    QBitArray bits(16);
    // Convert from QByteArray to QBitArray
    for(int i = 0; i < 2; ++i) {
        for(int b = 0; b < 8; ++b) {
            bits.setBit(i*8+b, size.at(i)&(1<<b));
        }
    }
    qDebug() << "bits " << bits;

    QString q;
    for (int i = 0; i < 3; ++i) {
        if (bits.at(i)) {
            q.append("1");
        } else {
            q.append("0");
        }
    }

    bool ok;
    int garbageSize = q.toInt(&ok, 2);

    QString tr;
    for (int i = 3; i < 16; ++i) {
        if (bits.at(i)) {
            tr.append("1");
        } else {
            tr.append("0");
        }
    }
    int treeSize = tr.toInt(&ok, 2);

    qDebug() << "g" << garbageSize << "t" << treeSize;

    QByteArray tree;
    qDebug() << qba.size();
    for (int i = 130; i < treeSize+130; ++i) {
        if (qba.at(i)) {
            tree.append(qba.at(i));
        }
    }

    qDebug() << "Tree: " << tree;

    Tree * t = new Tree(tree);

    // convert all data to QBitArray 'toDecode'
    // for (int i = 0; i < toDecode.size(); ++i
    //   traverse the tree; when bit is 0, go to the left; when bit is 1, go to the right
    //   if node is a leaf, get its key and append to QString 'decoded'
    // write in file with the original name

    return true;
}

bool Compress::compress() {
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();
    if (qba != 0) {
        CountOccurrence * co = new CountOccurrence(qba);
        QList<Occurrence> occur = co->orderByOccurrence();
        CreateHuffmanTree * cht = new CreateHuffmanTree(occur);
        Tree * tree = cht->createTree();
        cht->createHash(tree);

        QString data;
        for (int i = 0; i < qba.size(); ++i) {
            QString pathNode = cht->hash()->value(qba.at(i));
            data.append(pathNode);
        }
        int garbageSize = 8 - data.size()%8;
        if (garbageSize == 8) {
            garbageSize = 0;
        }
        for (int i = 0; i < garbageSize; ++i) {
            data.append("0");
        }

        QBitArray toByte;
        toByte.resize(data.size());
        for (int i = 0; i < data.size(); ++i) {
            if (data.at(i) == '0') {
                toByte[i] = true;
            }
            else {
                toByte[i] = false;
            }
        }

        bool ok;
        QByteArray encoded;
        for (int i = 0; i < data.size(); i+=8) {
            QString h = data.mid(i,i+8);
            encoded.append(QChar(h.toInt(&ok, 2)));
        }

        QString binaryGarbageSize = QString::number(garbageSize,2);
        QString binaryTreeSize = QString::number(tree->rep().size(),2);
        int zeros = 16 - (binaryGarbageSize.size() + binaryTreeSize.size());
        for (int i = 0; i < zeros; ++i) {
            binaryTreeSize.prepend(QString::number(0));
        }

        QString toBit = binaryGarbageSize;
        toBit.append(binaryTreeSize);

        int h1 = toBit.mid(0,8).toInt(&ok, 2);
        int h2 = toBit.mid(8,16).toInt(&ok, 2);;

        QByteArray toWrite;
        toWrite.resize(2);
        toWrite.clear();
        toWrite.append(QChar(h1));
        toWrite.append(QChar(h2));
        toWrite.append(m_fileName);

        for (int i = m_fileName.size(); i < 128; ++i ) {
            toWrite.append("#");
        }

        toWrite.append(tree->rep());
        toWrite.append(data);
        toWrite.append(encoded);

        f->write(encoded);
        qDebug() << m_fileName << " compressed";

        return true;
    } else {
        qDebug() << "file not found";

        return false;
    }
}


