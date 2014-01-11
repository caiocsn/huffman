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
    m_fileName = "";
    m_path = "";
}

bool Compress::uncompress() {
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();
    if (qba != 0) {
        QString size;
        size = qba.mid(0, 3); // why three?
        int c1 = size.at(0).unicode();
        int c2 = size.at(1).unicode();
        size.clear();

        QString s1 = fill(QString::number(c1, 2));
        QString s2 = fill(QString::number(c2, 2));
        size.append(s1);
        size.append(s2);

        s1.clear();
        s2.clear();
        for (int i = 0; i < 16; ++i) {
            if (i < 3) {
                s1.append(size.at(i));
            } else {
                s2.append(size.at(i));
            }
        }
        qDebug() << s1;
        bool ok;
        qDebug() << "a is" << s1.toInt(&ok, 2);;
        qDebug() << "b is" << s2.toInt(&ok, 2);;

        QString namefile;
        for (int i = 3; i < 130; ++i) { // why three?
            if (qba[i] == '#') {
                break;
            }
            namefile.append(qba.at(i));
        }

//        QString tr;
//        bool ok;
//        int treeSize = tr.toInt(&ok, 2);

//        QByteArray tree;
//        // qDebug() << qba.size();
//        for (int i = 130; i < treeSize+130; ++i) {
//            if (qba.at(i)) {
//                tree.append(qba.at(i));
//            }
//        }

//        qDebug() << "Tree: " << tree;

//        Tree * t = new Tree(tree);

        // convert all data to QBitArray 'toDecode'
        // for (int i = 0; i < toDecode.size(); ++i
        //   traverse the tree; when bit is 0, go to the left; when bit is 1, go to the right
        //   if node is a leaf, get its key and append to QString 'decoded'
        // write in file with the original name

        return true;
    } else {
        qDebug() << "404";
        return false;
    }
}

bool Compress::compress() {
    File * f = new File(m_path, m_fileName);
    QByteArray qba = f->read();
    if (qba != 0) {
        CountOccurrence * co = new CountOccurrence(qba);
        QList<Occurrence> occur = co->orderByOccurrence();
        CreateHuffmanTree * cht = new CreateHuffmanTree(occur);
        Tree * tree = cht->createTree();
        tree->createRep();
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
        qDebug() << toBit;

        int h1 = toBit.mid(0,8).toInt(&ok, 2);
        int h2 = toBit.mid(8,16).toInt(&ok, 2);

        QByteArray toWrite;
        toWrite.clear();
        toWrite.append(QChar(h1));
        toWrite.append(QChar(h2));
        toWrite.append(m_fileName);

        for (int i = m_fileName.size(); i < 128; ++i ) {
            toWrite.append("#");
        }

        toWrite.append(tree->rep());
        toWrite.append(encoded);

        f->write(toWrite);
        qDebug() << m_fileName << " compressed";

        return true;
    } else {
        qDebug() << "file not found";

        return false;
    }
}

QString Compress::fill(QString str)
{
    int zeros = 8 - str.size()%8;
    if (zeros == 8) {
        zeros = 0;
    }
    for (int i = 0; i < zeros; ++i) {
        str.prepend('0');
    }
    return str;
}


