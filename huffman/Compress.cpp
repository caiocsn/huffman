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

        bool ok;
        int garbageSize = s1.toInt(&ok, 2);
        int treeSize = s2.toInt(&ok, 2);

        QString namefile;
        for (int i = 3; i < 130; ++i) { // why three?
            if (qba[i] == '#') {
                break;
            }
            namefile.append(qba.at(i));
        }

        QString treeRep;
        treeRep = qba.mid(131, treeSize);

        Tree * tr = new Tree(treeRep);

        QString content;
        QString contentAux = qba.mid(treeSize+131, qba.size());
        for (int i = 0; i < contentAux.size(); ++i) {
            QChar simbol = contentAux.at(i);
            int unicode = simbol.unicode();
            content.append(fill(QString::number(unicode, 2)));
        }
        // QString content = contentAux.mid(0, contentAux.size()-garbageSize); // remove is better?
        qDebug() << "number of bytes of original file is " << qba.size() - (treeSize+131);

        qDebug() << "content is " << content;

        QByteArray decoded;
        Node * n = tr->root();
        for (int i = 0; i < content.size(); ++i) {
            if (n->isLeaf()) {
                decoded.append(n->key());
                n = tr->root();
            } else {
                if (content.at(i) == '0') {
                    n = n->left();
                } else if (content.at(i) == '1') {
                    n = n->right();
                } else {
                    qDebug() << "something is wrong here...";
                }
            }
        }
        qDebug() << "decoded is " << decoded;

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
        // fill data
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
        qDebug() << "encoded is " << encoded;
        qDebug() << "encodedS is " << encoded.size();

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


